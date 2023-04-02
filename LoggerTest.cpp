#include "Logger.hpp"

int main(){
    Logger::EnableAllLogger();
    std::cout << "標準出力へのテスト" << std::endl;
    auto logger = Logger::Get("myLogger");
    logger->Debug("debug");
    logger->Info("Info");
    logger->Critical("Critical");
    logger->Warning("Warning");
    std::cout << "disable this logger" << std::endl;
    logger->Disable();
    logger->Debug("このメッセージは見えないはずだよ");
    logger->Info("このメッセージは見えないはずだよ");
    logger->Warning("このメッセージは見えないはずだよ");
    logger->Critical("このメッセージは見えないはずだよ");
    std::cout << "enable this logger" << std::endl;
    logger->Enable();
    logger->Debug   ("このメッセージは見えるはずだよ");
    logger->Info    ("このメッセージは見えるはずだよ");
    logger->Warning ("このメッセージは見えるはずだよ");
    logger->Critical("このメッセージは見えるはずだよ");
}