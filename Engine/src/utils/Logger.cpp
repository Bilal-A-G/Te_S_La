#include "Logger.h"


std::shared_ptr<spdlog::logger> TESLA::Logger::m_clientLogger;
std::shared_ptr<spdlog::logger> TESLA::Logger::m_engineLogger;

void TESLA::Logger::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    m_clientLogger = spdlog::stderr_color_mt("APP");
    m_clientLogger->set_level(spdlog::level::trace);
    
    m_engineLogger = spdlog::stderr_color_mt("ENGINE");
    m_engineLogger->set_level(spdlog::level::trace);
}


