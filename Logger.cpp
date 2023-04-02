#include "Logger.hpp"
#include <chrono>

#ifdef LOGGER_HEADER_ONLY
    #define LOGGER_HEADER_ONLY_INLINE inline
#else
    #define LOGGER_HEADER_ONLY_INLINE
#endif // LOGGER_HEADER_ONLY

LOGGER_HEADER_ONLY_INLINE Logger::Logger(std::string_view loggerName, std::ostream& os):
loggerName(loggerName),
ostream(os),
isThisLoggerEnable(true)
{}

LOGGER_HEADER_ONLY_INLINE std::shared_ptr<Logger> Logger::Get(const std::string& loggerName, std::ostream& os) {
    auto&& loggerItr = Logger::loggerInstanceMap.find(loggerName);
    if(loggerItr != Logger::loggerInstanceMap.end()){
        return loggerItr->second;
    }
    std::shared_ptr<Logger> newLogger{new Logger{loggerName, os}};
    Logger::loggerInstanceMap.emplace(loggerName, newLogger);
    return newLogger;
}

LOGGER_HEADER_ONLY_INLINE void Logger::EnableAllLogger() noexcept{
    Logger::isAllLoggerEnable = true;
}

LOGGER_HEADER_ONLY_INLINE void Logger::DisableAllLogger() noexcept{
    Logger::isAllLoggerEnable = false;
}

LOGGER_HEADER_ONLY_INLINE bool Logger::IsAllLoggerEnable() noexcept{
    return Logger::isAllLoggerEnable;
}

LOGGER_HEADER_ONLY_INLINE std::string Logger::GetTimeString(const std::string& format) noexcept{
    auto&& currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* tm = std::localtime(&currentTime);
    char currentTimeStr[100];
    std::strftime(currentTimeStr, sizeof(currentTimeStr), format.c_str(), tm);
    return std::string{currentTimeStr};
}

LOGGER_HEADER_ONLY_INLINE void Logger::Enable() noexcept{
    this->isThisLoggerEnable = true;
}

LOGGER_HEADER_ONLY_INLINE void Logger::Disable() noexcept{
    this->isThisLoggerEnable = false;
}

LOGGER_HEADER_ONLY_INLINE bool Logger::IsEnable() noexcept{
    return this->isThisLoggerEnable;
}