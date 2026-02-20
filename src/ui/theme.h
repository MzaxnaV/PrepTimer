#ifndef THEME_HPP_
#define THEME_HPP_

#include "imgui.h"

namespace Theme {
    // Call once after ImGui::CreateContext()
    void Apply();

    // Fonts — access these to push/pop in specific widgets
    extern ImFont* FontUI;        // Inter Regular — general UI
    extern ImFont* FontUIBold;    // Inter Bold — labels, headings
    extern ImFont* FontTimer;     // JetBrains Mono — timer display
}

#endif // THEME_HPP_