#ifndef WINDOW_H_
#define WINDOW_H_

#include "app.h"

#include <windows.h>

HWND InitWindow(HINSTANCE hInstance, int width, int height, const wchar_t* title);
void ShutdownWindow();

// Resize, restyle, and reposition the main window to match the given mode.
// Call whenever g_app.mode changes.
void SetWindowMode(AppMode mode);

#endif // WINDOW_H_
