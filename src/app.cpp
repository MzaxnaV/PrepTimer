#include "app.h"

AppState g_app;

void ToggleExpanded()
{
    if (g_app.mode == AppMode::Expanded) {
        g_app.mode = g_app.mode_before_expand; // back to mini
    } else if (g_app.mode == AppMode::Running || g_app.mode == AppMode::Paused) {
        g_app.mode_before_expand = g_app.mode;
        g_app.mode = AppMode::Expanded;
    }
    // Window resizing is handled by the main loop on mode change
}
