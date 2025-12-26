#include "PrecompiledHeader.hpp"

#include <Mountain/Utils/Logger.hpp>

using namespace Mountain;

class LoggerEnvironment : public ::testing::Environment
{
public:
    void SetUp() override
    {
        Logger::Start();
    }

    void TearDown() override
    {
        Logger::Stop();
    }
};

// Register the environment
[[maybe_unused]] static const ::testing::Environment* const loggerEnv = ::testing::AddGlobalTestEnvironment(new LoggerEnvironment);

TEST(Utils_Logger, BasicLogging)
{
    Logger::Clear();
    const std::string msg = "Test message";
    Logger::LogInfo(msg);
    Logger::Synchronize();

    const auto& logs = Logger::GetLogList();
    ASSERT_FALSE(logs.empty());
    EXPECT_EQ(logs.back()->message, msg);
    EXPECT_EQ(logs.back()->level, Logger::LogLevel::Info);
}

TEST(Utils_Logger, Formatting)
{
    Logger::Clear();
    Logger::LogInfo("Value: {}", 42);
    Logger::Synchronize();

    const auto& logs = Logger::GetLogList();
    ASSERT_FALSE(logs.empty());
    EXPECT_EQ(logs.back()->message, "Value: 42");
}

TEST(Utils_Logger, MinimumLevel)
{
    Logger::Clear();
    const Logger::LogLevel oldLevel = Logger::minimumConsoleLevel;
    Logger::minimumConsoleLevel = Logger::LogLevel::Warning;

    Logger::LogInfo("Should not be logged");
    Logger::LogWarning("Should be logged");
    Logger::Synchronize();

    const auto& logs = Logger::GetLogList();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0]->message, "Should be logged");

    Logger::minimumConsoleLevel = oldLevel;
}

TEST(Utils_Logger, LogDebugSuppression)
{
    Logger::Clear();
    const Logger::LogLevel oldConsoleLevel = Logger::minimumConsoleLevel;
    const Logger::LogLevel oldFileLevel = Logger::minimumFileLevel;

    Logger::minimumConsoleLevel = Logger::LogLevel::Info;
    Logger::minimumFileLevel = Logger::LogLevel::Info;

    // Ensure no file is open
    if (Logger::HasFileOpen())
        Logger::CloseFile();

    DEBUG_LOG("This should be suppressed");
    Logger::Synchronize();

    EXPECT_TRUE(Logger::GetLogList().empty()) << "LogDebug was not suppressed from m_Logs when it should have been";

    Logger::minimumConsoleLevel = oldConsoleLevel;
    Logger::minimumFileLevel = oldFileLevel;
}
