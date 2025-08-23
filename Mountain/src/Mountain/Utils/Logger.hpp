#pragma once

#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <thread>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/DateTime.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "Mountain/Utils/Formatter.hpp"
#include "Mountain/Utils/Requirements.hpp"
#include "Mountain/Utils/TsQueue.hpp"

/// @file Logger.hpp
/// @brief Defines the Mountain::Logger static class

/// @brief Logs a debug log using the given format message and arguments.
#define DEBUG_LOG(message, ...) ::Mountain::Logger::LogDebug(message, __FILE__, __LINE__, __VA_ARGS__)

namespace Mountain
{
    /// @brief Static class used to log messages to the console and/or a file.
    ///
    /// ### Requirements
    /// Thread-safe logger that starts logging once @c Logger::Start() gets called, which is already done in @c Game::Game(). You can synchronize the calling thread
    /// with the logger one at any time by calling @c Logger::Synchronize. The logger needs to be stopped by calling @c Logger::Stop(), which is also already done in @c Game::~Game().
    ///
    /// ### Options
    /// By default, the logger doesn't log to a file. This can be changed by either calling @c Logger::OpenDefaultFile or @c Logger::OpenFile.
    /// You can also stop logging to the file whenever you want by calling @c Logger::CloseFile.
    ///
    /// You can change at any time the minimum LogLevel for either the console or the file by respectively setting @c Logger::minimumConsoleLevel or @c Logger::minimumFileLevel
    /// to a different value.
    ///
    /// ### Usage
    /// The most generic way of logging is by using the @c Logger::Log function, which allows you to pass a LogLevel to describe the severity
    /// of the log. Shortcuts are also available through the use of @c Logger::LogDebug, @c Logger::LogVerbose, @c Logger::LogInfo, @c Logger::LogWarning, @c Logger::LogError and @c Logger::LogFatal.
    /// Those functions take a format string and format parameters to follow the usage of <a href="https://en.cppreference.com/w/cpp/utility/format/format">std::format</a>.
    /// This means that any new parameter type that is directly printed must satisfy the requirements of the <a href="https://en.cppreference.com/w/cpp/utility/format/formattable">std::formattable</a>
    /// concept (defined a Requirements::Formattable in the Mountain namespace), and therefore needs to implement its own version of the <a href="https://en.cppreference.com/w/cpp/utility/format/formatter">std::formatter</a> struct.
    ///
    /// ### Example
    /// All logs are preceded by their timestamp (the exact time at which the @c Logger::Log function was called) and a string representation of their LogLevel.
    /// A typical log looks like the following:
    /// @code
    /// [11:26:05.751] [INFO] Starting logging to file.
    /// @endcode
    /// Also, @ref Logger::LogLevel::Debug "debug logs" automatically specify the file and line at which the log was made.
    class Logger final
    {
        STATIC_CLASS(Logger)

    public:
        /// @brief Describes the severity of a log.
        enum class LogLevel : uint8_t
        {
            /// @brief Log intended for temporary debugging only.
            ///
            /// Preceded by '[TEMP DEBUG]' and appears green in the console.
            /// Temporary debug logs are not printed in the log file by default, and they are only printed in the console if in a debug build.
            Debug,
            /// @brief Log intended for debugging only.
            ///
            /// Preceded by '[DEBUG]' and appears gray in the console.
            /// Verbose logs are not printed in the log file by default, and they are only printed in the console if in a debug build.
            Verbose,
            /// @brief Log intended for general information.
            ///
            /// Preceded by '[INFO]' and appears white in the console.
            /// Info logs are not printed in the log file by default.
            Info,
            /// @brief Log intended for warnings.
            ///
            /// Preceded by '[WARN]' and appears orange in the console.
            Warning,
            /// @brief Log intended for errors.
            ///
            /// Preceded by '[ERROR]' and appears red in the console.
            Error,
            /// @brief Log intended for fatal errors.
            ///
            /// Preceded by '[FATAL]' and appears red and bold in the console.
            /// After such a log, the program is not intended to continue to function normally and should instead exit ASAP.
            Fatal
        };

    private:
        struct LogEntry
        {
            std::string message;
            LogLevel level;
            DateTime time;

            bool_t printToConsole, printToFile;

            std::string file;
            int32_t line = -1;

            bool_t sameAsPrevious = false;

            std::shared_ptr<LogEntry> previousLog = nullptr;

            MOUNTAIN_API LogEntry();

            MOUNTAIN_API LogEntry(std::string&& message, LogLevel level);

            MOUNTAIN_API LogEntry(std::string&& message, LogLevel level, const std::string& file, int32_t line);

            MOUNTAIN_API LogEntry(std::string&& message, LogLevel level, DateTime timePoint);

            MOUNTAIN_API bool_t operator==(const LogEntry& other) const;
        };

        // We thought about using std::list here instead, but because the allocations are made on the logger thread anyway, we can make it a std::vector
        MOUNTAIN_API static inline std::vector<std::shared_ptr<LogEntry>> m_Logs;

    public:
        /// @brief The minimum necessary LogLevel for a log to be printed in the console.
        ///
        /// Defaults to LogLevel::Debug in a debug build, or LogLevel::Info otherwise.
        MOUNTAIN_API static inline LogLevel minimumConsoleLevel =
#ifdef _DEBUG
            LogLevel::Debug;
#else
            LogLevel::Info;
#endif

        /// @brief The minimum necessary LogLevel for a log to be printed in the log file.
        ///
        /// Defaults to LogLevel::Info.
        MOUNTAIN_API static inline LogLevel minimumFileLevel =
#ifdef _DEBUG
            LogLevel::Info;
#else
            LogLevel::Warning;
#endif

        /// @brief Logs a message using the specified format string, arguments and LogLevel.
        ///
        /// @tparam Args The format arguments types. These are generally automatically deducted by the compiler and often don't need to be manually specified. Also, they must satisfy the Requirements::Formattable concept requirements.
        /// @param level The log severity.
        /// @param format The format string to log.
        /// @param args The arguments to replace the format string with.
        ///
        /// @see <a href="https://en.cppreference.com/w/cpp/utility/format/spec">The standard format specification</a>
        template <Requirements::Formattable... Args>
        static void Log(LogLevel level, const std::string& format, Args&&... args);

        /// @brief Logs a temporary debug message using the current file, line, specified format string and arguments.
        ///
        /// This function shouldn't be used directly. To print a temporary debug log message, instead use DEBUG_LOG.
        ///
        /// @see Log
        /// @see LogLevel::Debug
        template <Requirements::Formattable... Args>
        static void LogDebug(const std::string& format, const char_t* file, int32_t line, Args&&... args);

        /// @brief Logs a debug message using the specified format string and arguments.
        ///
        /// @see Log
        template <Requirements::Formattable... Args>
        static void LogVerbose(const std::string& format, Args&&... args);

        /// @brief Logs an information message using the specified format string and arguments.
        ///
        /// @see Log
        template <Requirements::Formattable... Args>
        static void LogInfo(const std::string& format, Args&&... args);

        /// @brief Logs a warning message using the specified format string and arguments.
        ///
        /// @see Log
        template <Requirements::Formattable... Args>
        static void LogWarning(const std::string& format, Args&&... args);

        /// @brief Logs an error message using the specified format string and arguments.
        ///
        /// @see Log
        template <Requirements::Formattable... Args>
        static void LogError(const std::string& format, Args&&... args);

        /// @brief Logs a fatal error message using the specified format string and arguments.
        ///
        /// @see Log
        template <Requirements::Formattable... Args>
        static void LogFatal(const std::string& format, Args&&... args);

        /// @brief Opens a file for logging.
        ///
        /// If a file is already open for logging e.g. if Logger::HasFileOpen returns @c true, this overwrites it with the new file.
        ///
        /// @param filepath The file to open and to log into.
        MOUNTAIN_API static void OpenFile(const std::filesystem::path& filepath);

        /// @brief Opens the default log file.
        ///
        /// The default log file is an autogenerated one with a name corresponding to the current date and the @c .log file extension.
        /// An example of a default log file: @c 2024-02-13.log.
        /// If this is called multiple times in a day (by launching the program multiple times during the same day for example), this appends to the
        /// already existing log file.
        MOUNTAIN_API static void OpenDefaultFile();

        /// @brief Returns whether the logger is already log to a file.
        MOUNTAIN_API static bool HasFileOpen();

        /// @brief Closes the current log file.
        MOUNTAIN_API static void CloseFile();

        /// @brief Synchronizes the calling thread with the logger one, and makes sure all logs have been printed before returning.
        MOUNTAIN_API static void Synchronize();

        /// @brief Starts the logger.
        ///
        /// This function is called automatically when the Game is constructed.
        /// After a call to this function, you can use the Log functions.
        ///
        /// This function doesn't do anything if the logger has already been started.
        MOUNTAIN_API static void Start();

        /// @brief Synchronizes the threads and stops the logger.
        ///
        /// This function is called automatically when the Game is destroyed.
        /// After a call to this function, logger function calls won't do anything.
        ///
        /// This function doesn't do anything if the logger has already been stopped.
        MOUNTAIN_API static void Stop();

        MOUNTAIN_API static const decltype(m_Logs)& GetLogList();

        MOUNTAIN_API static void Clear();

    private:
        MOUNTAIN_API static inline TsQueue<std::shared_ptr<LogEntry>> m_NewLogs;

        MOUNTAIN_API static inline std::shared_ptr<LogEntry> m_LastLog;

        MOUNTAIN_API static inline bool_t m_LastLogCollapsed = false;

        MOUNTAIN_API static inline std::condition_variable m_CondVar;

        MOUNTAIN_API static void Run();

        MOUNTAIN_API static inline std::thread m_Thread;

        MOUNTAIN_API static inline std::mutex m_Mutex;

        MOUNTAIN_API static inline bool_t m_Running = false;

        MOUNTAIN_API static inline bool_t m_Synchronizing = false;

        MOUNTAIN_API static inline std::ofstream m_File;

        MOUNTAIN_API static inline std::filesystem::path m_Filepath;

        MOUNTAIN_API static inline uint32_t m_LogIndex = 0;

        MOUNTAIN_API static void PushLog(const std::shared_ptr<LogEntry>& log);

        /// @brief Prints a log to the console and the logging file.
        MOUNTAIN_API static void PrintLog(const std::shared_ptr<LogEntry>& log);

        /// @brief Builds the given log's prefix. Returns the [prefix, color] pair.
        MOUNTAIN_API static std::pair<std::string, const char_t*> BuildLogPrefix(const std::shared_ptr<LogEntry>& log);
    };
}

// Start of Logger.inl

#include <format>
#include <utility>

namespace Mountain
{
    template <Requirements::Formattable... Args>
    void Logger::Log(const LogLevel level, const std::string& format, Args&&... args)
    {
        if (level < minimumConsoleLevel && level < minimumFileLevel)
            return;

        PushLog(std::make_shared<LogEntry>(std::vformat(format, std::make_format_args(args...)), level));
    }

    template <Requirements::Formattable... Args>
    void Logger::LogDebug(const std::string& format, const char_t* file, const int32_t line, Args&&... args)
    {
        if (LogLevel::Debug < minimumConsoleLevel && LogLevel::Debug < minimumFileLevel)
            return;

        PushLog(std::make_shared<LogEntry>(std::vformat(format, std::make_format_args(args...)), LogLevel::Debug, file, line));
    }

    template <Requirements::Formattable... Args>
    void Logger::LogVerbose(const std::string& format, Args&&... args)
    {
        Logger::Log(LogLevel::Verbose, format, std::forward<Args>(args)...);
    }

    template <Requirements::Formattable... Args>
    void Logger::LogInfo(const std::string& format, Args&&... args)
    {
        Logger::Log(LogLevel::Info, format, std::forward<Args>(args)...);
    }

    template <Requirements::Formattable... Args>
    void Logger::LogWarning(const std::string& format, Args&&... args)
    {
        Logger::Log(LogLevel::Warning, format, std::forward<Args>(args)...);
    }

    template <Requirements::Formattable... Args>
    void Logger::LogError(const std::string& format, Args&&... args)
    {
        Logger::Log(LogLevel::Error, format, std::forward<Args>(args)...);
    }

    template <Requirements::Formattable... Args>
    void Logger::LogFatal(const std::string& format, Args&&... args)
    {
        Logger::Log(LogLevel::Fatal, format, std::forward<Args>(args)...);
    }
}
