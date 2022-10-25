#pragma once

#if TS_DYNAMIC_LINK
#ifdef TS_ENGINE
#define TS_DLL __declspec(dllexport)
#else
#define TS_DLL __declspec(dllimport)
#endif
#else
#define TS_DLL
#endif