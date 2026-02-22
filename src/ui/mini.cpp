#include "mini.h"
#include "theme.h"
#include "../app.h"

#include "imgui.h"

#include <cstdio>

void RenderMiniContent()
{
    // Pre-compute display strings so we can measure them before drawing
    StrBuf timerStr = FormatTime(g_app.session.timer.ElapsedMs());
    StrBuf avgStr   = FormatTime(g_app.session.timer.AverageLapMs());

    char avgWithPipeBuf[32];
    snprintf(avgWithPipeBuf, sizeof(avgWithPipeBuf), "%s |", avgStr.data);

    const char* sectionStr = SectionName(g_app.session.current_section);

    // Measure text sizes with their respective fonts
    ImGui::PushFont(Theme::FontTimer);
    ImVec2 timerSize = ImGui::CalcTextSize(timerStr.data);
    ImGui::PopFont();

    ImGui::PushFont(Theme::FontTimerSm);
    ImVec2 avgWithPipeSize = ImGui::CalcTextSize(avgWithPipeBuf);
    ImGui::PopFont();

    ImGui::PushFont(Theme::FontUI);
    ImVec2 sectionSize = ImGui::CalcTextSize(sectionStr);
    ImGui::PopFont();

    // Center the row within the window
    float  spacing  = ImGui::GetStyle().ItemSpacing.x;
    float  totalW   = timerSize.x + spacing + avgWithPipeSize.x + spacing + sectionSize.x;
    ImVec2 winSize  = ImGui::GetWindowSize();
    ImVec2 pad      = ImGui::GetStyle().WindowPadding;
    float  contentW = winSize.x - pad.x * 2.0f;
    float  contentH = winSize.y - pad.y * 2.0f;

    float startX = pad.x + (contentW - totalW) * 0.5f;
    float startY = pad.y + (contentH - timerSize.y) * 0.5f;

    // Main timer — large monospace bold
    ImGui::SetCursorPos(ImVec2(startX, startY));
    ImGui::PushFont(Theme::FontTimer);
    ImGui::Text("%s", timerStr.data);
    ImGui::PopFont();

    ImGui::SameLine();

    // Avg time + pipe — small monospace bold, vertically centered
    ImGui::PushFont(Theme::FontTimerSm);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (timerSize.y - avgWithPipeSize.y) * 0.5f - 8.0f);
    ImGui::TextDisabled("%s", avgWithPipeBuf);
    ImGui::PopFont();

    ImGui::SameLine();

    // Section label — Inter UI font, vertically centered
    ImGui::PushFont(Theme::FontUI);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (timerSize.y - sectionSize.y) * 0.5f - 8.0f);
    ImGui::TextDisabled("%s", sectionStr);
    ImGui::PopFont();

    // Click anywhere on the mini strip to expand the session view
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        ToggleExpanded();
}
