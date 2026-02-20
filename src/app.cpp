#include "app.h"
#include "window.h"

AppState g_app = { .mode = AppMode::Running };

void ToggleExpanded()
{
    if (g_app.mode == AppMode::Expanded) {
        g_app.mode = AppMode::Idle;
        SetWindowTopmost(true);   // back to mini mode
    } else {
        g_app.mode = AppMode::Expanded;
        SetWindowTopmost(false);  // expanded doesn't need topmost
    }
}