#ifndef LOGGER_HPP

#include <iostream>
#include <string_view>
#include <chrono>
#include <unordered_map>
#include <memory>

using namespace std::string_view_literals;

class Logger{
private:
    static inline bool isAllLoggerEnable = true;
    static inline std::unordered_map<std::string, std::shared_ptr<Logger>> loggerInstanceMap;

    std::string loggerName;
    std::ostream& ostream;
    bool isThisLoggerEnable;

    std::string GetTimeString(const std::string& format = "%Y-%m-%d %H:%I:%S") noexcept;
    Logger(std::string_view loggerName, std::ostream& os = std::cout);
public:
    static std::shared_ptr<Logger> Get(const std::string& loggerName, std::ostream& os = std::cout);
    static void EnableAllLogger() noexcept;    
    static void DisableAllLogger() noexcept;
    static bool IsAllLoggerEnable() noexcept;

    void Enable() noexcept;
    void Disable() noexcept;
    bool IsEnable() noexcept;

    template <class ...Args>
    void PrintLog(std::string_view logLevel, Args ...args){
        if(!this->isAllLoggerEnable || !this->isThisLoggerEnable){
            return;
        }
        this->ostream << "[" << this->GetTimeString("%Y-%m-%d %H:%I:%S") << "] [" << loggerName <<  "] [" << logLevel << "] " ;
        (this->ostream << ... << args);
        this->ostream << std::endl;
    }

    template <class ...Args>
    void Debug(Args ...args){
        constexpr std::string_view LOG_LEVEL = "Debug"sv;
        this->PrintLog(LOG_LEVEL, args...);
    }

    template <class ...Args>
    void Info(Args ...args){
        constexpr std::string_view LOG_LEVEL = "Info"sv;
        this->PrintLog(LOG_LEVEL, args...);
    }

    template <class ...Args>
    void Warning(Args ...args){
        constexpr std::string_view LOG_LEVEL = "Warning"sv;
        this->PrintLog(LOG_LEVEL, args...);
    }

    template <class ...Args>
    void Critical(Args ...args){
        constexpr std::string_view LOG_LEVEL = "Critical"sv;
        this->PrintLog(LOG_LEVEL, args...);
    }
};

#ifdef LOGGER_HEADER_ONLY
#include "Logger.cpp"
#endif 

#endif // LOGGER_HPP