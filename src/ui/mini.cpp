#include "mini.h"
#include "theme.h"
#include "../app.h"

#include "imgui.h"

void RenderMiniContent()
{
    // Timer — large monospace font
    ImGui::PushFont(Theme::FontTimer);
    ImGui::Text("%s", FormatTime(g_app.session.timer.ElapsedMs()).data);
    ImGui::PopFont();

    ImGui::SameLine();

    // avg + section — smaller UI font, vertically centered against the timer
    ImGui::PushFont(Theme::FontUI);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f);
    ImGui::TextDisabled("avg %s | %s",
        FormatTime(g_app.session.timer.AverageLapMs()).data,
        SectionName(g_app.session.current_section));
    ImGui::PopFont();

    // Click anywhere on the mini strip to expand the session view
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        ToggleExpanded();
}
