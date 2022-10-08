#pragma once

#ifdef TS_ENGINE
#define TS_DLL __declspec(dllexport)
#else
#define TS_DLL __declspec(dllimport)
#endif