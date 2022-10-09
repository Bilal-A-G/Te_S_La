#pragma once
#include "../utils/Logger.h"

inline bool runApplication = true;

namespace TESLA
{
    inline void ExitApplication()
    {
        runApplication = false;
    }
}

extern void Init();
extern void Render();
extern void CleanUp();

int main(int argc, char* argv[])
{
    TESLA::Logger::Init();
    TS_LOG_MESSAGE(spdlog::level::info, "Initialization successful");
    
    Init();

    while (runApplication)
    {
        Render();
    }

    CleanUp();
}
