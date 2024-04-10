#include <Windows.h>
#include "WinMenu.h"
#include <iostream>

#define DebugPrint OutputDebugString

HWND lHandle;

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam) 
{
	switch (Msg)
	{
	case WM_HOTKEY:
		if (WinMenu::wHandle != NULL && GetWindowLong(WinMenu::wHandle, GWL_STYLE) & WS_VISIBLE)
		{
			ShowWindowAsync(WinMenu::wHandle, SW_HIDE);
			break;
		}
		else {
			ShowWindowAsync(WinMenu::wHandle, SW_SHOW);
		}
		DebugPrint(L"Hotkey pressed\n");
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wc = { };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Handler";
	RegisterClassEx(&wc);
	WinMenu::Initialize(hInstance);

	lHandle = CreateWindowExW(WS_EX_NOACTIVATE, L"Handler", L"Handler", NULL, 0, 0, 800, 600, HWND_MESSAGE, nullptr, hInstance, nullptr);

	RegisterHotKey(lHandle, 1, MOD_NOREPEAT | MOD_WIN, 0x59);

	MSG msg = { };
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}