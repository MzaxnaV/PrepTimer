#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>

HWND InitWindow(HINSTANCE hInstance, int width, int height, const wchar_t* title);
void ShutdownWindow();
void SetWindowTopmost(bool topmost);

#endif // WINDOW_H_