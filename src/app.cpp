#include "app.h"
#include "window.h"

AppState g_app;

void ToggleExpanded()
{
    if (g_app.mode == AppMode::Expanded) {
        g_app.mode = g_app.mode_before_expand;  // restore previous state
        SetWindowTopmost(true);
    } else if (g_app.mode == AppMode::Running || g_app.mode == AppMode::Paused) {
        g_app.mode_before_expand = g_app.mode;  // remember current state
        g_app.mode = AppMode::Expanded;
        SetWindowTopmost(false);
    }
}