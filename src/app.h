#ifndef APP_H_
#define APP_H_

#include "timer.h"

enum class AppMode {
    Idle,       // no session running, mini window hidden
    Running,    // session active, mini window visible
    Paused,     // session paused, mini window visible
    Expanded    // expanded window open
};

struct AppState {
    AppMode mode = AppMode::Idle;
    Timer timer;
};

extern AppState g_app;

void ToggleExpanded();

#endif // APP_H_