#include "renderer.h"
#include "window.h"
#include "ui/theme.h"
#include "ui/mini.h"
#include "ui/session_view.h"
#include "app.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "implot.h"

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    HWND hwnd = InitWindow(hInstance, 1, 1, L"Prep Timer");
    if (!hwnd)
        return 1;

    if (!InitD3D(hwnd)) {
        MessageBoxW(nullptr,
                    L"Failed to initialize Direct3D 11.",
                    L"Prep Timer",
                    MB_OK | MB_ICONERROR);
        DestroyWindow(hwnd);
        ShutdownWindow();
        return 1;
    }

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    Theme::Apply();

    ImPlot::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(GetDevice(), GetContext());

    SetWindowMode(AppMode::Idle);

    // Main loop
    bool done         = false;
    AppMode last_mode = AppMode::Idle;

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

        // Resize/restyle the window whenever mode changes
        if (g_app.mode != last_mode) {
            SetWindowMode(g_app.mode);
            last_mode = g_app.mode;
        }

        // Start ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Process hotkeys — must be after NewFrame so IsKeyPressed reads current-frame IO
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

        // Tighter padding in mini mode so the timer text fits
        bool isMini = (g_app.mode == AppMode::Running || g_app.mode == AppMode::Paused);
        if (isMini)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));

        // Single full-screen ImGui canvas — content switches with mode
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);
        ImGui::Begin("##main",
                     nullptr,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                         ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus |
                         ImGuiWindowFlags_NoNav);

        switch (g_app.mode) {
        case AppMode::Idle:
            RenderSessionStart();
            break;
        case AppMode::Running:
        case AppMode::Paused:
            RenderMiniContent();
            break;
        case AppMode::Expanded:
            RenderSessionActive();
            break;
        }

        ImGui::End();

        if (isMini)
            ImGui::PopStyleVar();

        // Render
        ImGui::Render();
        BeginFrame(0.1f, 0.1f, 0.1f);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
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
