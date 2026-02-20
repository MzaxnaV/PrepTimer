#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "implot.h"

#include <windows.h>

#include "renderer.h"
#include "window.h"
#include "ui/theme.h"
#include "ui/mini.h"
#include "ui/session_view.h"
#include "app.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

    HWND hwnd = InitWindow(hInstance, 1280, 800, L"Prep Timer");

    InitD3D(hwnd);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    Theme::Apply();

    ImPlot::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(GetDevice(), GetContext());

    // -----------------------------------------------------------------------
    // Main loop
    // -----------------------------------------------------------------------
    bool done = false;
    while (!done) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        if (g_app.mode == AppMode::Running || g_app.mode == AppMode::Paused) {
            if (ImGui::IsKeyPressed(ImGuiKey_L, false))
                g_app.session.timer.RecordLap();

            if (ImGui::IsKeyPressed(ImGuiKey_P, false)) {
                if (g_app.mode == AppMode::Paused) {
                    g_app.session.timer.Resume();
                    g_app.mode = AppMode::Running;
                } else {
                    g_app.session.timer.Pause();
                    g_app.mode = AppMode::Paused;
                }
            }
        }

        // Start ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // ---- UI goes here ---------
        if (g_app.mode == AppMode::Idle)
            RenderSessionStart();
        else if (g_app.mode == AppMode::Expanded)
            RenderSessionActive();
        RenderMiniWindow(); // TODO: remove later, just to verify everything works
        // ---------------------------

        // Render
        ImGui::Render();
        BeginFrame(0.1f, 0.1f, 0.1f);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Multi-viewport rendering
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        EndFrame();
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    DestroyWindow(hwnd);
    ShutdownD3D();
    ShutdownWindow();

    return 0;
}