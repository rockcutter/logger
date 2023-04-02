#include "Logger.hpp"
#include <sstream>
#include <cassert>
#include <gtest/gtest.h>
#include <regex>

TEST(LoggerTest, GetLoggerInstance){
    std::stringstream ss;

    auto&& logger1 = Logger::Get("test1", ss);
    auto&& logger2 = Logger::Get("test2", ss);

    EXPECT_NE(logger1, nullptr);
    EXPECT_NE(logger2, nullptr);
    EXPECT_EQ(logger1, Logger::Get("test1", ss));
    EXPECT_EQ(logger2, Logger::Get("test2", ss));
}

TEST(LoggerTest, LogOutput) {
    std::stringstream ss;
    auto logger = Logger::Get("LogOutput", ss);
    logger->Debug("debug message");
    logger->Info("info message");
    logger->Warning("warning message");
    logger->Critical("critical message");
    auto output_str = ss.str();
    EXPECT_NE(output_str.find("[Debug] debug message"), std::string::npos);
    EXPECT_NE(output_str.find("[Info] info message"), std::string::npos);
    EXPECT_NE(output_str.find("[Warning] warning message"), std::string::npos);
    EXPECT_NE(output_str.find("[Critical] critical message"), std::string::npos);
}

TEST(LoggerTest, EnableDisable) {
    std::stringstream ss;
    auto logger = Logger::Get("EnableDisable", ss);
    logger->Debug("debug message");
    logger->Disable();
    logger->Debug("debug message");
    logger->Enable();
    logger->Debug("debug message");
    auto&& outputStr = ss.str();
    auto&& firstMessagePos = outputStr.find("[Debug] debug message");
    auto&& secondMessagePos = outputStr.find("[Debug] debug message", firstMessagePos + 1);
    EXPECT_NE(outputStr.find("[Debug] debug message"), std::string::npos);
    EXPECT_EQ(outputStr.find("[Debug] debug message", secondMessagePos + 1), std::string::npos);
}

TEST(LoggerTest, EnableDisableAll) {
    std::stringstream ss;
    auto logger1 = Logger::Get("EnableDisableAll1", ss);
    auto logger2 = Logger::Get("EnableDisableAll2", ss);
    Logger::EnableAllLogger();
    logger1->Debug("debug message1");
    logger2->Debug("debug message2");
    Logger::DisableAllLogger();
    logger1->Debug("debug message1");
    logger2->Debug("debug message2");
    auto outputStr = ss.str();
    EXPECT_NE(outputStr.find("[Debug] debug message1"), std::string::npos);
    EXPECT_NE(outputStr.find("[Debug] debug message2"), std::string::npos);
    EXPECT_EQ(outputStr.find("[Debug] debug message1", outputStr.find("[Debug] debug message1") + 1), std::string::npos);
    EXPECT_EQ(outputStr.find("[Debug] debug message2", outputStr.find("[Debug] debug message2") + 1), std::string::npos);
}

TEST(LoggerTest, LoggerEnableDisable) {
    std::stringstream ss;
    auto logger = Logger::Get("LoggerEnableDisable", ss);

    logger->Disable();
    EXPECT_FALSE(logger->IsEnable());

    logger->Enable();
    EXPECT_TRUE(logger->IsEnable());
}

TEST(LoggerTest, LoggerOutput) {
    std::stringstream ss;
    auto logger = Logger::Get("LoggerOutput", ss);
    logger->DisableAllLogger();

    logger->Debug("This is a debug message");
    logger->Info("This is an info message");
    logger->Warning("This is a warning message");
    logger->Critical("This is a critical message");

    EXPECT_EQ(ss.str(), "");
    logger->EnableAllLogger();

    logger->Debug("This is a debug message");
    logger->Info("This is an info message");
    logger->Warning("This is a warning message");
    logger->Critical("This is a critical message");

    std::string expectedOutput = R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\] \[LoggerOutput\] \[Debug\] This is a debug message
\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\] \[LoggerOutput\] \[Info\] This is an info message
\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\] \[LoggerOutput\] \[Warning\] This is a warning message
\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\] \[LoggerOutput\] \[Critical\] This is a critical message
)";

    auto&& l = Logger::Get("Console");
    l->Debug(ss.str());
    std::regex pattern(expectedOutput, std::regex_constants::ECMAScript | std::regex_constants::icase);
    EXPECT_TRUE(std::regex_match(ss.str(), pattern));
}