#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// ===== struct =====
struct MenuItem {
    int id;
    std::wstring name;
    double price;
};

// ===== global variables =====
extern std::vector<MenuItem> menu;
extern int scrollOffset;
extern std::vector<HWND> addButtons;

// ===== constants =====
#define BTN_CART 500
#define BTN_ADD_BASE 5000

// ===== function prototypes =====
void LoadMenuData();

int GetMaxScroll(int clientH, int itemCount);
void UpdateScrollBar(HWND hwnd, int contentItems);

void DrawMenu(HDC hdc, RECT rc);
void DrawCart(HDC hdc);
void ShowAddButtons(bool show);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                         WPARAM wParam, LPARAM lParam);
HWND CreateMenuWindow(HINSTANCE hInstance);