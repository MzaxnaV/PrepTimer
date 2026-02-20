#include "window.h"

#include "imgui_impl_win32.h"

#include <windows.h>

#include "renderer.h"

static WNDCLASSEXW g_wc = {};

// -----------------------------------------------------------------------
// Win32 message handler
// -----------------------------------------------------------------------
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
                                                             LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        if (GetDevice() != nullptr && wParam != SIZE_MINIMIZED) {
            OnWindowResize(LOWORD(lParam), HIWORD(lParam));
        }
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

HWND InitWindow(HINSTANCE hInstance, int width, int height, const wchar_t* title) {
    // Register window class
    g_wc = {.cbSize = sizeof(g_wc),
            .style = CS_CLASSDC,
            .lpfnWndProc = WndProc,
            .hInstance = hInstance,
            .lpszClassName = L"PrepTimer"};
    RegisterClassExW(&g_wc);

    HWND hwnd = CreateWindowW(g_wc.lpszClassName, title, WS_OVERLAPPEDWINDOW, 100, 100, width,
                              height, nullptr, nullptr, g_wc.hInstance, nullptr);

    return hwnd;
}

void ShutdownWindow() { UnregisterClassW(g_wc.lpszClassName, g_wc.hInstance); }
