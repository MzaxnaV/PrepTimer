#include "theme.h"
#include "imgui.h"

namespace Theme {

ImFont* FontUI     = nullptr;
ImFont* FontUIBold = nullptr;
ImFont* FontTimer  = nullptr;

void Apply()
{
    // -----------------------------------------------------------------------
    // Fonts
    // -----------------------------------------------------------------------
    ImGuiIO& io = ImGui::GetIO();

    // Base UI font — Inter Regular at 16px
    FontUI = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Inter-Regular.ttf", 16.0f);

    // Bold variant for labels and headings
    FontUIBold = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Inter-Bold.ttf", 16.0f);

    // Timer font — JetBrains Mono, larger for the mini widget
    FontTimer = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/JetBrainsMono-Regular.ttf", 32.0f);

    // Fallback to default if font files not found
    if (!FontUI)     FontUI     = io.Fonts->AddFontDefault();
    if (!FontUIBold) FontUIBold = io.Fonts->AddFontDefault();
    if (!FontTimer)  FontTimer  = io.Fonts->AddFontDefault();

    // -----------------------------------------------------------------------
    // Colors
    // -----------------------------------------------------------------------
    ImVec4* colors = ImGui::GetStyle().Colors;

    // Backgrounds
    colors[ImGuiCol_WindowBg]         = ImVec4(0.067f, 0.067f, 0.067f, 1.0f); // #111111
    colors[ImGuiCol_ChildBg]          = ImVec4(0.110f, 0.110f, 0.110f, 1.0f); // #1C1C1C
    colors[ImGuiCol_PopupBg]          = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_FrameBg]          = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_FrameBgActive]    = ImVec4(0.200f, 0.200f, 0.200f, 1.0f);

    // Headers (collapsibles, table headers)
    colors[ImGuiCol_Header]           = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_HeaderHovered]    = ImVec4(0.200f, 0.200f, 0.200f, 1.0f);
    colors[ImGuiCol_HeaderActive]     = ImVec4(0.290f, 0.569f, 1.000f, 0.3f);

    // Accent — #4A9EFF blue
    colors[ImGuiCol_CheckMark]        = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);
    colors[ImGuiCol_SliderGrab]       = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.400f, 0.700f, 1.000f, 1.0f);

    // Buttons
    colors[ImGuiCol_Button]           = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_ButtonHovered]    = ImVec4(0.290f, 0.620f, 1.000f, 0.8f);
    colors[ImGuiCol_ButtonActive]     = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);

    // Tabs
    colors[ImGuiCol_Tab]              = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_TabHovered]       = ImVec4(0.290f, 0.620f, 1.000f, 0.6f);
    colors[ImGuiCol_TabActive]        = ImVec4(0.290f, 0.620f, 1.000f, 0.9f);
    colors[ImGuiCol_TabUnfocused]     = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);

    // Title bar
    colors[ImGuiCol_TitleBg]          = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);

    // Borders
    colors[ImGuiCol_Border]           = ImVec4(0.165f, 0.165f, 0.165f, 1.0f); // #2A2A2A
    colors[ImGuiCol_BorderShadow]     = ImVec4(0.000f, 0.000f, 0.000f, 0.0f);

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg]      = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab]    = ImVec4(0.200f, 0.200f, 0.200f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.250f, 0.250f, 0.250f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);

    // Text
    colors[ImGuiCol_Text]             = ImVec4(0.910f, 0.910f, 0.910f, 1.0f); // #E8E8E8
    colors[ImGuiCol_TextDisabled]     = ImVec4(0.400f, 0.400f, 0.400f, 1.0f);

    // Separator
    colors[ImGuiCol_Separator]        = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.290f, 0.620f, 1.000f, 0.6f);
    colors[ImGuiCol_SeparatorActive]  = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);

    // -----------------------------------------------------------------------
    // Style / geometry
    // -----------------------------------------------------------------------
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding    = 8.0f;
    style.ChildRounding     = 6.0f;
    style.FrameRounding     = 4.0f;
    style.PopupRounding     = 6.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 4.0f;
    style.TabRounding       = 4.0f;

    style.WindowPadding     = ImVec2(12.0f, 12.0f);
    style.FramePadding      = ImVec2(8.0f,  5.0f);
    style.ItemSpacing       = ImVec2(8.0f,  6.0f);
    style.ItemInnerSpacing  = ImVec2(6.0f,  4.0f);
    style.IndentSpacing     = 20.0f;

    style.WindowBorderSize  = 1.0f;
    style.FrameBorderSize   = 0.0f;
    style.PopupBorderSize   = 1.0f;

    style.ScrollbarSize     = 10.0f;
    style.GrabMinSize       = 8.0f;
}

} // namespace Theme