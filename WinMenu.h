#pragma once
#include <Windows.h>
#include <iostream>

#define DebugPrint OutputDebugString

#ifndef WIDTH
#define WIDTH 800
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif

LRESULT CALLBACK WinMenuProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);

class WinMenu {
public:
	static inline HWND wHandle;
	static inline HWND textHandle;
	static HWND Initialize(HINSTANCE hInstance);
};