#include <Windows.h>
#include <iostream>

#define DebugPrint OutputDebugString

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam) 
{
	switch (Msg)
	{
	case WM_HOTKEY:
		DebugPrint(L"Hotkey pressed\n");
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASSEX wc = { };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Main";
	RegisterClassEx(&wc);

	HWND handle = CreateWindowExW(WS_EX_NOACTIVATE, L"Main", L"Main", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, HWND_MESSAGE, nullptr, hInstance, nullptr);

	RegisterHotKey(handle, 1, MOD_NOREPEAT | MOD_WIN, 0x59);

	MSG msg = { };
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}