#include "session_view.h"
#include "theme.h"
#include "../app.h"
#include "../session.h"

#include "imgui.h"

#include <cstring>

// Persistent input buffers
static char s_name_buf[128] = {};
static char s_tag_buf[64]   = {};

void RenderSessionStart()
{
    ImGui::PushFont(Theme::FontUIBold);
    ImGui::Text("Session Name");
    ImGui::PopFont();
    ImGui::SetNextItemWidth(-1);
    ImGui::InputText("##name", s_name_buf, sizeof(s_name_buf));

    ImGui::Spacing();

    ImGui::PushFont(Theme::FontUIBold);
    ImGui::Text("Tags");
    ImGui::PopFont();
    ImGui::TextDisabled("comma separated, e.g.  mock, arithmetic, weak");
    ImGui::SetNextItemWidth(-1);
    ImGui::InputText("##tags", s_tag_buf, sizeof(s_tag_buf));

    ImGui::Spacing();

    ImGui::PushFont(Theme::FontUIBold);
    ImGui::Text("Starting Section");
    ImGui::PopFont();

    Section& sec = g_app.session.current_section;
    if (ImGui::RadioButton("None",  sec == Section::None))  sec = Section::None;
    ImGui::SameLine();
    if (ImGui::RadioButton("QA",    sec == Section::QA))    sec = Section::QA;
    ImGui::SameLine();
    if (ImGui::RadioButton("DILR",  sec == Section::DILR))  sec = Section::DILR;
    ImGui::SameLine();
    if (ImGui::RadioButton("VARC",  sec == Section::VARC))  sec = Section::VARC;

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushFont(Theme::FontUIBold);
    ImGui::Text("Target per question");
    ImGui::PopFont();

    int target_s = (int)(g_app.session.target_ms / 1000);
    ImGui::SetNextItemWidth(120);
    if (ImGui::InputInt("seconds##target", &target_s)) {
        if (target_s < 10)  target_s = 10;   // minimum 10 seconds
        if (target_s > 600) target_s = 600;  // maximum 10 minutes
        g_app.session.target_ms = (uint32_t)(target_s * 1000);
    }

    ImGui::Spacing();

    bool can_start = s_name_buf[0] != '\0';
    if (!can_start) ImGui::BeginDisabled();

    if (ImGui::Button("Start Session", ImVec2(-1, 36))) {
        g_app.session.name = s_name_buf;
        g_app.session.tags.clear();

        // Parse comma-separated tags
        std::string tag_str = s_tag_buf;
        std::string token;
        for (char c : tag_str) {
            if (c == ',') {
                size_t start = token.find_first_not_of(' ');
                if (start != std::string::npos)
                    g_app.session.tags.push_back(token.substr(start));
                token.clear();
            } else {
                token += c;
            }
        }
        if (!token.empty()) {
            size_t start = token.find_first_not_of(' ');
            if (start != std::string::npos)
                g_app.session.tags.push_back(token.substr(start));
        }

        g_app.session.unix_start =
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();

        g_app.session.timer.Start();
        g_app.mode = AppMode::Running;  // main loop calls SetWindowMode

        std::memset(s_name_buf, 0, sizeof(s_name_buf));
        std::memset(s_tag_buf,  0, sizeof(s_tag_buf));
    }

    if (!can_start) {
        ImGui::EndDisabled();
        ImGui::TextDisabled("session name required");
    }
}

void RenderSessionActive()
{
    ImGui::Text("Session: %s", g_app.session.name.c_str());
    ImGui::SameLine();
    ImGui::TextDisabled("[%s]", SectionName(g_app.session.current_section));

    ImGui::Separator();
    ImGui::Spacing();

    // Current question timer
    ImGui::PushFont(Theme::FontTimer);
    ImGui::Text("%s", FormatTime(g_app.session.timer.ElapsedMs()));
    ImGui::PopFont();

    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    ImGui::TextDisabled("avg %s", FormatTime(g_app.session.timer.AverageLapMs()));

    ImGui::Spacing();

    if (ImGui::Button("Lap (L)", ImVec2(100, 32)))
        g_app.session.timer.RecordLap();

    bool is_paused = g_app.mode_before_expand == AppMode::Paused;

    ImGui::SameLine();
    const char* pause_label = is_paused ? "Resume (P)" : "Pause (P)";
    if (ImGui::Button(pause_label, ImVec2(110, 32))) {
        if (is_paused) {
            g_app.session.timer.Resume();
            g_app.mode_before_expand = AppMode::Running;
        } else {
            g_app.session.timer.Pause();
            g_app.mode_before_expand = AppMode::Paused;
        }
    }

    if (ImGui::Button("Minimize", ImVec2(100, 32)))
        ToggleExpanded();

    ImGui::SameLine();
    if (ImGui::Button("End Session", ImVec2(110, 32))) {
        g_app.session.timer.Pause();
        g_app.session.timer.Reset();
        g_app.session.timer.laps.clear();
        g_app.mode = AppMode::Idle;  // main loop calls SetWindowMode
        // TODO: save session to disk
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushFont(Theme::FontUIBold);
    ImGui::Text("Laps");
    ImGui::PopFont();

    ImGui::BeginChild("##laps", ImVec2(0, 0), true);
    const auto& laps = g_app.session.timer.laps;
    for (int i = 0; i < (int)laps.size(); i++)
        ImGui::Text("Q%-3d  %s", i + 1, FormatTime(laps[i].duration_ms));
    ImGui::EndChild();
}
