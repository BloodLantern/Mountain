module Mountain:Utils_Logger;

import std;
import :Core_Types;
import :Utils_Formatter;

#define ANSI_COLOR_GRAY     "\x1b[38;5;242m"
#define ANSI_COLOR_GREEN    "\x1b[0;32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_RED      "\x1b[31m"

#define ANSI_STYLE_BOLD     "\x1b[1m"

#define ANSI_RESET          "\x1b[0m"

using namespace Mountain;

void Logger::OpenFile(const std::filesystem::path &filepath)
{
    CloseFile();

    const bool_t exists = std::filesystem::exists(filepath);
    if (!exists)
    {
        create_directories(filepath.parent_path());
    }

    m_File.open(filepath, std::ios_base::out | std::ios_base::app);
    m_Filepath = filepath;

    if (!m_File.is_open() || !m_File.good())
    {
        LogWarning("Could not open log file for writing: {}", absolute(filepath));
        return;
    }

    // Separate the current logs from the previous ones using a newline
    if (exists)
        m_File << '\n';

    LogInfo("Logging to file: {}", filepath);
    // Prevent this log from being printed to the file
    m_NewLogs.Back()->printToFile = false;

    LogInfo("Starting logging #{}", m_LogIndex);
}

void Logger::OpenDefaultFile()
{
    const auto&& now = std::chrono::system_clock::now();
    const auto&& time = std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::floor<std::chrono::seconds>(now))
                .get_local_time().time_since_epoch();

    // Get the current date and format it in yyyy-mm-dd for the directory name
    const std::string dateStr = std::format("{:%Y-%m-%d}", now);
    // Get the current date and format it in hh-mm-ss for the file name
    const std::string timeStr = std::format("{:%H-%M-%S}", std::chrono::hh_mm_ss(time).to_duration() - std::chrono::floor<std::chrono::days>(now).time_since_epoch());

    const std::filesystem::path directory = std::filesystem::path("logs") / dateStr;
    const std::filesystem::path filepath = directory / (timeStr + ".log");

    if (!exists(directory))
    {
        OpenFile(filepath);
        return;
    }

    // Count the number of existing logs to get the log index
    // Start at -1 so that we get index-like numbers, e.g. 0 for the first one, 1 for the second one, etc...
    int32_t fileCount = -1;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
    {
        if (is_regular_file(entry))
            fileCount++;
    }

    m_LogIndex = fileCount;
    OpenFile(filepath);
}

bool Logger::HasFileOpen()
{
    return m_File.is_open();
}

void Logger::CloseFile()
{
    if (!m_File.is_open())
        return;

    m_File.flush();
    m_File.close();

    copy_file(m_Filepath, m_Filepath.parent_path() / "latest.log", std::filesystem::copy_options::overwrite_existing);
}

void Logger::Synchronize()
{
    if (m_NewLogs.Empty())
        return;

    m_Synchronizing = true;
    m_CondVar.notify_one();
    std::unique_lock lock(m_Mutex);
    m_CondVar.wait(lock, [] { return !m_Synchronizing; });
}

void Logger::Start()
{
    if (m_Running)
        return;

    LogInfo("Starting logger");

    m_Running = true;

    m_Thread = std::thread(Run);
}

void Logger::Stop()
{
    if (!m_Running)
        return;

    LogInfo("Stopping logger");

    m_Running = false;
    m_CondVar.notify_one();

    if (m_Thread.joinable())
        m_Thread.join();

    CloseFile();
}

const decltype(Logger::m_Logs)& Logger::GetLogList() { return m_Logs; }

void Logger::Clear() { m_Logs.clear(); }

Logger::LogEntry::LogEntry()
    : level(LogLevel::Info)
    , printToConsole(false)
    , printToFile(false)
{
}

Logger::LogEntry::LogEntry(std::string&& message, const LogLevel level)
    : LogEntry(
        std::move(message),
        level,
        std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now()))
            .get_local_time().time_since_epoch()
    )
{
}

Logger::LogEntry::LogEntry(std::string&& message, const LogLevel level, const std::string& file, const int32_t line)
    : LogEntry(
        std::move(message),
        level,
        std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now()))
            .get_local_time().time_since_epoch()
    )
{
    this->file = file;
    this->line = line;
}

Logger::LogEntry::LogEntry(
    std::string&& message,
    const LogLevel level,
    const std::chrono::system_clock::time_point timePoint
)
    : message(std::move(message))
    , level(level)
    , time(timePoint - std::chrono::floor<std::chrono::days>(timePoint))
    , printToConsole(level >= minimumConsoleLevel)
    , printToFile(level >= minimumFileLevel)
{
}

Logger::LogEntry::LogEntry(
    std::string&& message,
    const LogLevel level,
    const std::chrono::system_clock::duration duration
)
    : message(std::move(message))
    , level(level)
    , time(duration - std::chrono::floor<std::chrono::days>(duration))
    , printToConsole(level >= minimumConsoleLevel)
    , printToFile(level >= minimumFileLevel)
{
}

bool_t Logger::LogEntry::operator==(const LogEntry& other) const { return message == other.message && level == other.level && printToConsole == other.printToConsole && printToFile == other.printToFile; }

void Logger::Run()
{
    // Set thread name for easier debugging
    Utils::SetThreadName(m_Thread, L"Logger Thread");

    // Detach this thread from the main one to make sure it finishes normally
    m_Thread.detach();

    std::unique_lock lock(m_Mutex);
    while (m_Running || !m_NewLogs.Empty())
    {
        m_CondVar.wait(lock, [] { return !m_NewLogs.Empty() || !m_Running || m_Synchronizing; });

        m_Logs.reserve(m_Logs.size() + m_NewLogs.Count());

        while (!m_NewLogs.Empty())
        {
            auto&& log = m_NewLogs.Pop();

            // Check if the log is equal to the previous one
            if (log->previousLog && *log->previousLog == *log)
                log->sameAsPrevious = true;

            // Add the log to the list
            m_Logs.push_back(log);

            // Print the log to the console and/or the file
            PrintLog(log);
        }

        // As we don't use std::endl for newlines, make sure to flush the streams before going back to sleep
        std::cout.flush();
        if (m_File.is_open())
            m_File.flush();

        if (m_Synchronizing)
        {
            m_Synchronizing = false;
            m_CondVar.notify_one();
        }
    }

    m_Logs.clear();
}

void Logger::PushLog(const std::shared_ptr<LogEntry>& log)
{
    m_NewLogs.Push(log);
    if (m_LastLog)
        log->previousLog = m_LastLog;
    m_LastLog = log;

    m_CondVar.notify_one();
}

void Logger::PrintLog(const std::shared_ptr<LogEntry>& log)
{
    static uint64_t sameLastLogs;
    static decltype(sameLastLogs) oldSameLastLogs;

    oldSameLastLogs = sameLastLogs;
    if (log->sameAsPrevious)
        sameLastLogs++;
    else
        sameLastLogs = 0;

    auto&& prefix = BuildLogPrefix(log);
    const std::string& baseMessage = prefix.first;
    const char_t* const color = prefix.second;

    const bool_t printToFile = log->printToFile && m_File.is_open();

    // If the last log is the same as the current one, we should collapse this one
    if (sameLastLogs > 0)
    {
        if (log->printToConsole)
        {
            // If we already printed the same log, move the cursor back to the beginning of the line
            if (sameLastLogs > 1)
                std::cout << '\r';

            std::cout << color + baseMessage + "[...and " + std::to_string(sameLastLogs) + " more]" + ANSI_RESET;
        }

        // If we need to print to a file, we first wait for a different log

        m_LastLogCollapsed = true;
    }
    else
    {
        const std::string message = baseMessage + log->message + '\n';

        if (log->printToConsole)
        {
            if (m_LastLogCollapsed)
                std::cout << '\n';
            std::cout << color + message + ANSI_RESET;
        }

        if (printToFile)
        {
            if (m_LastLogCollapsed)
                m_File << BuildLogPrefix(log->previousLog).first + "[...and " + std::to_string(oldSameLastLogs) + " more]\n";
            else
                m_File << message;
        }

        m_LastLogCollapsed = false;
    }

    log->previousLog.reset();
}

std::pair<std::string, const char_t*> Logger::BuildLogPrefix(const std::shared_ptr<LogEntry>& log)
{
    // Get the message time and format it in [hh:mm:ss:ms]
    const auto&& t = std::chrono::duration_cast<std::chrono::milliseconds, int64_t>(log->time.time_since_epoch());
    const std::string time = std::format("[{:%T}] ", t);

    std::string baseMessage;
    const char_t* color = ANSI_RESET;
    switch (log->level)
    {
        case LogLevel::Debug:
            color = ANSI_COLOR_GREEN;
            baseMessage = time + "[TEMP DEBUG] " + log->file + "(" + std::to_string(log->line) + "): ";
            break;

        case LogLevel::Verbose:
            color = ANSI_COLOR_GRAY;
            baseMessage = time + "[DEBUG] ";
            break;

        case LogLevel::Info:
            baseMessage = time + "[INFO] ";
            break;

        case LogLevel::Warning:
            color = ANSI_COLOR_YELLOW;
            baseMessage = time + "[WARN] ";
            break;

        case LogLevel::Error:
            color = ANSI_COLOR_RED;
            baseMessage = time + "[ERROR] ";
            break;

        case LogLevel::Fatal:
            color = ANSI_STYLE_BOLD ANSI_COLOR_RED;
            baseMessage = time + "[FATAL] ";
            break;
    }

    return std::make_pair(baseMessage, color);
}
