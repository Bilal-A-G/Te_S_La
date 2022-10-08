#pragma once

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
    Init();

    while (runApplication)
    {
        Render();
    }

    CleanUp();
}
