#include "window.h"

#include "app.h"
#include "renderer.h"

#include "imgui_impl_win32.h"

#include <windows.h>

static WNDCLASSEXW g_wc    = {};
static HWND        g_hwnd  = nullptr;

// -----------------------------------------------------------------------
// Win32 message handler
// -----------------------------------------------------------------------
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
                                                             LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED && GetDevice() != nullptr)
                OnWindowResize(LOWORD(lParam), HIWORD(lParam));
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU)
                return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

HWND InitWindow(HINSTANCE hInstance, int width, int height, const wchar_t* title)
{
    g_wc = {.cbSize        = sizeof(g_wc),
            .style         = CS_CLASSDC,
            .lpfnWndProc   = WndProc,
            .hInstance     = hInstance,
            .lpszClassName = L"PrepTimer"};
    RegisterClassExW(&g_wc);

    g_hwnd = CreateWindowExW(0,
        g_wc.lpszClassName, title, WS_OVERLAPPEDWINDOW,
        100, 100, width, height,
        nullptr, nullptr, g_wc.hInstance, nullptr);

    return g_hwnd;
}

void ShutdownWindow()
{
    UnregisterClassW(g_wc.lpszClassName, g_wc.hInstance);
}

void SetWindowMode(AppMode mode)
{
    RECT wa;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &wa, 0);

    if (mode == AppMode::Running || mode == AppMode::Paused) {
        // Mini: borderless popup, always-on-top, anchored bottom-right
        constexpr int W = 268, H = 64;
        int x = wa.right  - W - 8;
        int y = wa.bottom - H - 8;

        SetWindowLongW(g_hwnd, GWL_STYLE,   WS_POPUP | WS_VISIBLE);
        SetWindowLongW(g_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
        SetWindowPos(g_hwnd, HWND_TOPMOST, x, y, W, H,
                     SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    } else {
        // Idle or Expanded: standard window with title bar
        int cw = (mode == AppMode::Expanded) ? 660 : 440;
        int ch = (mode == AppMode::Expanded) ? 540 : 430;

        DWORD style   = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
        DWORD exStyle = 0;

        // Compute outer size for the desired client area
        RECT r = {0, 0, cw, ch};
        AdjustWindowRectEx(&r, style, FALSE, exStyle);
        int w = r.right  - r.left;
        int h = r.bottom - r.top;

        // Center on work area
        int x = wa.left + (wa.right  - wa.left - w) / 2;
        int y = wa.top  + (wa.bottom - wa.top  - h) / 2;

        SetWindowLongW(g_hwnd, GWL_STYLE,   style);
        SetWindowLongW(g_hwnd, GWL_EXSTYLE, exStyle);
        SetWindowPos(g_hwnd, HWND_NOTOPMOST, x, y, w, h,
                     SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    }
}
