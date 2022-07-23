#pragma once


class LoggerManager
{
public:

    static LoggerManager &GetInstance();
    inline virtual ~LoggerManager(){}
    std::shared_ptr<spdlog::logger> GetLogger();
protected:

private:

    static std::unique_ptr<LoggerManager> instance_;
    static std::once_flag gOnceFlag;
    LoggerManager();
    LoggerManager(const LoggerManager& rs) = delete;
    LoggerManager(LoggerManager &&rs) = delete;
    LoggerManager& operator = (const LoggerManager& rs) = delete;
    LoggerManager& operator = (LoggerManager&& rs) = delete;
    std::shared_ptr<spdlog::logger> p_Logger;
    static constexpr std::uint64_t max_size = 1048576 * 5;
    static constexpr std::uint16_t max_files = 3;
};