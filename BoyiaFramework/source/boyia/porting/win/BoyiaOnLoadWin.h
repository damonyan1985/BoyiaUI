#ifndef BoyiaOnLoadWin_h
#define BoyiaOnLoadWin_h

#include <Windows.h>

#ifdef _WINDLL
#define BOYIA_PORTING_API __declspec(dllexport)
#else
#define BOYIA_PORTING_API __declspec(dllimport)
#endif

class BOYIA_PORTING_API BoyiaOnLoadWin
{
public:
	static void setContextWin(HWND hwnd);
};

#endif