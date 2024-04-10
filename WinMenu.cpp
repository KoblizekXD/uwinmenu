#include "WinMenu.h"

HWND WinMenu::Initialize(HINSTANCE hInstance)
{
    WNDCLASSEX wc = { };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WinMenuProc;
    wc.lpszClassName = L"Main";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(30, 30, 30));
    RegisterClassEx(&wc);
    // WS_POPUPWINDOW;
    WinMenu::wHandle = CreateWindowExW(NULL, L"Main", L"Main", WS_POPUPWINDOW, 0, 0, WIDTH, HEIGHT, NULL, nullptr, hInstance, nullptr);
    HRGN hRgn = CreateRoundRectRgn(0, 0, WIDTH - 1, HEIGHT - 1, 20, 20);
    SetWindowRgn(WinMenu::wHandle, hRgn, TRUE);
    return WinMenu::wHandle;
}

LRESULT WinMenuProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HRGN hRgn = CreateRoundRectRgn(0, 0, WIDTH - 4, HEIGHT - 4, 20, 20);
        // GetWindowRgn(hWnd, hRgn);
		HDC hdc = BeginPaint(hWnd, &ps);
		FrameRgn(hdc, hRgn, CreateSolidBrush(RGB(113, 96, 232)), 2, 2);
		EndPaint(hWnd, &ps);
		break;
    }
    case WM_SHOWWINDOW: {
        int cx = GetSystemMetrics(SM_CXSCREEN);
        int cy = GetSystemMetrics(SM_CYSCREEN);
        SetWindowPos(
            WinMenu::wHandle,
            HWND_TOPMOST,
            (cx / 2) - (WIDTH / 2),
            (cy / 2) - (HEIGHT / 2),
            0,
            0,
            SWP_NOSIZE
        );
        break;
    }
    case WM_CLOSE:
        ShowWindow(hWnd, SW_HIDE);
        break;
    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
    return 0;
}
