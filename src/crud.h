#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "menu.h"

extern Menu g_menu;

// Window procedure
LRESULT CALLBACK CrudWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
// create admin account window
HWND createaccountadmin(HINSTANCE hInstance, HWND owner = NULL);

// create main menu window
HWND CreateMenuWindow(HINSTANCE hInstance);