#include "theme.h"
#include "../resource.h"
#include "imgui.h"

#include <windows.h>

namespace {

// Returns a pointer into the exe's mapped image for the given RCDATA resource.
// out_size receives the byte count. Returns nullptr on failure.
static void* ResData(int id, int& out_size)
{
    HRSRC   hRes = FindResourceW(nullptr, MAKEINTRESOURCEW(id), reinterpret_cast<LPCWSTR>(RT_RCDATA));
    if (!hRes) return nullptr;
    HGLOBAL hMem = ::LoadResource(nullptr, hRes);
    if (!hMem) return nullptr;
    out_size = static_cast<int>(SizeofResource(nullptr, hRes));
    return LockResource(hMem);
}

} // namespace

namespace Theme {

ImFont* FontUI      = nullptr;
ImFont* FontUIBold  = nullptr;
ImFont* FontTimer   = nullptr;
ImFont* FontTimerSm = nullptr;

void Apply()
{
    // Fonts — loaded from embedded RCDATA resources (no external files required)
    ImGuiIO& io = ImGui::GetIO();

    // FontDataOwnedByAtlas = false: the data lives in the exe image, ImGui must not free it.
    ImFontConfig cfg;
    cfg.FontDataOwnedByAtlas = false;

    int sz = 0;

    // Base UI font — Inter Regular at 16px
    if (void* d = ResData(IDR_FONT_INTER_REGULAR, sz))
        FontUI = io.Fonts->AddFontFromMemoryTTF(d, sz, 16.0f, &cfg);

    // Bold variant for labels and headings
    if (void* d = ResData(IDR_FONT_INTER_BOLD, sz))
        FontUIBold = io.Fonts->AddFontFromMemoryTTF(d, sz, 16.0f, &cfg);

    // Timer font — JetBrains Mono Bold, larger for the mini widget
    if (void* d = ResData(IDR_FONT_JETBRAINS_MONO_BOLD, sz))
        FontTimer = io.Fonts->AddFontFromMemoryTTF(d, sz, 40.0f, &cfg);

    // Small mono font — JetBrains Mono Bold at 16px for avg time in mini
    if (void* d = ResData(IDR_FONT_JETBRAINS_MONO_BOLD, sz))
        FontTimerSm = io.Fonts->AddFontFromMemoryTTF(d, sz, 16.0f, &cfg);

    // Fallback to default if resource loading fails
    if (!FontUI)
        FontUI = io.Fonts->AddFontDefault();
    if (!FontUIBold)
        FontUIBold = io.Fonts->AddFontDefault();
    if (!FontTimer)
        FontTimer = io.Fonts->AddFontDefault();
    if (!FontTimerSm)
        FontTimerSm = io.Fonts->AddFontDefault();

    // Colors
    ImVec4* colors = ImGui::GetStyle().Colors;

    // Backgrounds
    colors[ImGuiCol_WindowBg]       = ImVec4(0.067f, 0.067f, 0.067f, 1.0f); // #111111
    colors[ImGuiCol_ChildBg]        = ImVec4(0.110f, 0.110f, 0.110f, 1.0f); // #1C1C1C
    colors[ImGuiCol_PopupBg]        = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_FrameBg]        = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_FrameBgActive]  = ImVec4(0.200f, 0.200f, 0.200f, 1.0f);

    // Headers (collapsibles, table headers)
    colors[ImGuiCol_Header]        = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.0f);
    colors[ImGuiCol_HeaderActive]  = ImVec4(0.290f, 0.569f, 1.000f, 0.3f);

    // Accent — #4A9EFF blue
    colors[ImGuiCol_CheckMark]        = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);
    colors[ImGuiCol_SliderGrab]       = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.400f, 0.700f, 1.000f, 1.0f);

    // Buttons
    colors[ImGuiCol_Button]        = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.290f, 0.620f, 1.000f, 0.8f);
    colors[ImGuiCol_ButtonActive]  = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);

    // Tabs
    colors[ImGuiCol_Tab]                = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_TabHovered]         = ImVec4(0.290f, 0.620f, 1.000f, 0.6f);
    colors[ImGuiCol_TabActive]          = ImVec4(0.290f, 0.620f, 1.000f, 0.9f);
    colors[ImGuiCol_TabUnfocused]       = ImVec4(0.110f, 0.110f, 0.110f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);

    // Title bar
    colors[ImGuiCol_TitleBg]          = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);

    // Borders
    colors[ImGuiCol_Border]       = ImVec4(0.165f, 0.165f, 0.165f, 1.0f); // #2A2A2A
    colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.0f);

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.067f, 0.067f, 0.067f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.200f, 0.200f, 0.200f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.250f, 0.250f, 0.250f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);

    // Text
    colors[ImGuiCol_Text]         = ImVec4(0.910f, 0.910f, 0.910f, 1.0f); // #E8E8E8
    colors[ImGuiCol_TextDisabled] = ImVec4(0.400f, 0.400f, 0.400f, 1.0f);

    // Separator
    colors[ImGuiCol_Separator]        = ImVec4(0.165f, 0.165f, 0.165f, 1.0f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.290f, 0.620f, 1.000f, 0.6f);
    colors[ImGuiCol_SeparatorActive]  = ImVec4(0.290f, 0.620f, 1.000f, 1.0f);

    // Style / geometry
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding    = 8.0f;
    style.ChildRounding     = 6.0f;
    style.FrameRounding     = 4.0f;
    style.PopupRounding     = 6.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 4.0f;
    style.TabRounding       = 4.0f;

    style.WindowPadding    = ImVec2(12.0f, 12.0f);
    style.FramePadding     = ImVec2(8.0f, 5.0f);
    style.ItemSpacing      = ImVec2(8.0f, 6.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
    style.IndentSpacing    = 20.0f;

    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize  = 0.0f;
    style.PopupBorderSize  = 1.0f;

    style.ScrollbarSize = 10.0f;
    style.GrabMinSize   = 8.0f;
}

} // namespace Theme