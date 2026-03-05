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
extern bool showCartPage;
extern std::vector<HWND> addButtons;

// ===== constants =====
#define BTN_CART 500
#define BTN_ADD_BASE 1000

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



// ===== class =====
class Menu {
public:
    std::vector<MenuItem> m;

    void LoadCSV(const std::string& filename);
    bool SaveCSV(const std::string& filename);

    void CREATE(const MenuItem& item);
    void Read();
    void Delete(int id);
    void Update(int id, const MenuItem& newItem);

    bool CheckId(int id) const;
};