#pragma once
#include "../core/Core.h"
#include "spdlog/spdlog.h"
#include"spdlog/sinks/stdout_color_sinks.h"

namespace TESLA
{
    class TS_DLL Logger
    {
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger> GetEngineLogger() {return m_engineLogger;}
        static std::shared_ptr<spdlog::logger> GetClientLogger(){return m_clientLogger;}
    private:
        static std::shared_ptr<spdlog::logger> m_engineLogger;
        static std::shared_ptr<spdlog::logger> m_clientLogger;
        
    };
}

#ifdef TS_DEBUG
#ifdef TS_ENGINE
#define TS_LOG_MESSAGE(...) ::TESLA::Logger::GetEngineLogger()->log(__VA_ARGS__)
#else
#define TS_LOG_MESSAGE(...) ::TESLA::Logger::GetClientLogger()->log(__VA_ARGS__)
#endif
#else
#define TS_LOG_MESSAGE(...) 
#endif
