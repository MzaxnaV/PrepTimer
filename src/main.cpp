#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "implot.h"

#include <windows.h>

#include "renderer.h"
#include "window.h"
#include "ui/theme.h"
#include "ui/mini.h"
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

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(GetDevice(), GetContext());

    g_app.session.timer.Start(); // TODO: remove this


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

        if (ImGui::IsKeyPressed(ImGuiKey_L, false))
            g_app.session.timer.RecordLap();

        // Start ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // ---- UI goes here ---------
        RenderMiniWindow(); // TODO: remove later, just to verify everything works
        // ---------------------------

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