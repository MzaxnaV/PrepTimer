#include "mini.h"
#include "theme.h"
#include "../app.h"
#include "imgui.h"

#include <windows.h>

void RenderMiniWindow()
{
    // Only render when a session is active
    if (g_app.mode != AppMode::Running && g_app.mode != AppMode::Paused)
        return;

    // Get taskbar height so we can sit just above it
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    float screenRight  = (float)workArea.right;
    float screenBottom = (float)workArea.bottom;

    // Mini window size
    constexpr float W = 260.0f;
    constexpr float H = 56.0f;

    // Position: bottom-left, just above taskbar
    // ImGui::SetNextWindowPos(ImVec2(screenRight - W - 8.0f, screenBottom - H - 32.0f),
    //                         ImGuiCond_Always);

    // Position: middle temp.
    ImGui::SetNextWindowPos(ImVec2(screenRight/2 - W, screenBottom/2 - H), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(W, H), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.92f);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar              |
        ImGuiWindowFlags_NoResize                |
        ImGuiWindowFlags_NoScrollbar             |
        ImGuiWindowFlags_NoMove                  |
        ImGuiWindowFlags_NoSavedSettings         |
        ImGuiWindowFlags_NoBringToFrontOnFocus   |
        ImGuiWindowFlags_NoNav                   |
        ImGuiWindowFlags_NoDocking;

    ImGui::Begin("##mini", nullptr, flags);

    // Timer font for the numbers
    ImGui::PushFont(Theme::FontTimer);

    ImGui::Text("%s", FormatTime(g_app.session.timer.ElapsedMs()));

    ImGui::PopFont();

    ImGui::SameLine();

    // avg label in regular font
    ImGui::PushFont(Theme::FontUI);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f); // vertically center against timer font
    ImGui::TextDisabled("avg %s | %s",
        FormatTime(g_app.session.timer.AverageLapMs()),
        SectionName(g_app.session.current_section));
    ImGui::PopFont();

    // Click anywhere on mini window to expand
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        ToggleExpanded();

    ImGui::End();
}