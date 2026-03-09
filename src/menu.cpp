#include "menu.h"
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <vector>
#include <string>
#include"cart_ui.h"
std::vector<MenuItem> menu;
std::vector<HWND> addButtons;
int scrollOffset = 0;
HWND hCartButton = NULL;
bool isCartOpen = false;

// ================= LOAD CSV =================
void LoadMenuData() {
    menu.clear();

    std::wifstream file(L"..//data/menu.csv");
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        MessageBoxW(NULL, L"Cannot open menu.csv", L"Error", MB_OK);
        return;
    }

    std::wstring line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        std::wstringstream ss(line);
        std::wstring idStr, name, priceStr;

        getline(ss, idStr, L',');
        getline(ss, name, L',');
        getline(ss, priceStr, L',');

        MenuItem item;
        item.id = std::stoi(idStr);
        item.name = name;
        item.price = std::stod(priceStr);

        menu.push_back(item);
    }

    file.close();
}

// ================= SCROLL =================
int GetMaxScroll(int clientH, int itemCount) {
    int columns = 3;
    int rows = (itemCount + columns - 1) / columns;

    int boxH = 250;
    int gapY = 120;

    int contentHeight = rows * (boxH + gapY);
    int visibleHeight = clientH - 150;

    if (contentHeight <= visibleHeight)
        return 0;

    return contentHeight - visibleHeight;
}

void UpdateScrollBar(HWND hwnd) {
    RECT rc;
    GetClientRect(hwnd, &rc);

    SCROLLINFO si{};
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;

    int maxScroll = GetMaxScroll(rc.bottom, menu.size());

    si.nMin = 0;
    si.nMax = maxScroll;
    si.nPage = 100;   // สำคัญ! ถ้า 0 Windows จะ disable thumb
    si.nPos = scrollOffset;

    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
}

// ================= DRAW MENU =================
void DrawMenu(HWND hwnd, HDC hdc, RECT rc) {

    HFONT fontTitle = CreateFontW(30,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
        DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,VARIABLE_PITCH,L"Segoe UI");

    HFONT fontMenu = CreateFontW(20,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,
        DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,VARIABLE_PITCH,L"Segoe UI");

    SetBkMode(hdc, TRANSPARENT);

    SelectObject(hdc, fontTitle);
    TextOutW(hdc, 40, 20, L"Restaurant Menu", 15);

    int padding = 120;
    int gapX = 60;
    int gapY = 120;
    int columns = 3;

    int availableWidth = rc.right - (padding * 2);
    int totalGap = gapX * (columns - 1);
    int boxW = (availableWidth - totalGap) / columns;
    int boxH = 250;

    int startX = padding;
    int startY = 100 - scrollOffset;

    SelectObject(hdc, fontMenu);

    for (size_t i = 0; i < menu.size(); i++) {

        int col = i % columns;
        int row = i / columns;

        int x = startX + col * (boxW + gapX);
        int y = startY + row * (boxH + gapY);

        if (y > rc.bottom || y + boxH < 0)
            continue;

        Rectangle(hdc, x, y, x + boxW, y + boxH);

        RECT nameRect = {x+20, y+20, x+boxW-20, y+boxH-80};
        DrawTextW(hdc, menu[i].name.c_str(), -1,
                  &nameRect, DT_LEFT | DT_WORDBREAK);

        std::wstring priceText =
            std::to_wstring((int)menu[i].price) + L" Baht";

        RECT priceRect = {
            x,
            y + boxH + 10,
            x + boxW,
            y + boxH + 45
        };

        DrawTextW(hdc, priceText.c_str(), -1,
                  &priceRect,
                  DT_CENTER | DT_SINGLELINE | DT_VCENTER);

        int btnX = x + boxW - 110;
        int btnY = y + boxH - 70;

        if (addButtons.size() <= i) {
            HWND btn = CreateWindowW(
                L"BUTTON", L"Add",
                WS_VISIBLE | WS_CHILD,
                btnX, btnY,
                90, 35,
                hwnd,
                (HMENU)(BTN_ADD_BASE + i),
                NULL, NULL
            );
            addButtons.push_back(btn);
        } else {
            MoveWindow(addButtons[i], btnX, btnY, 90, 35, TRUE);
        }
    }

    DeleteObject(fontTitle);
    DeleteObject(fontMenu);
}

// ================= WNDPROC =================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                         WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
        LoadMenuData();

        hCartButton = CreateWindowW(
            L"BUTTON", L"Cart",
            WS_VISIBLE | WS_CHILD,
            0, 0, 120, 40,
            hwnd, (HMENU)BTN_CART,
            NULL, NULL);

       startCartPage(hwnd);

        hideCartPage();

        showMenuPage(hwnd);

        UpdateScrollBar(hwnd);
        break;

    case WM_SIZE:
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        if (hCartButton)
            MoveWindow(hCartButton, rc.right - 150, 20, 120, 40, TRUE);

        UpdateScrollBar(hwnd);
    }
    break;

    case WM_MOUSEWHEEL:
    {
         if(isCartOpen){
            SendMessage(borderTable, WM_MOUSEWHEEL, wParam, lParam);
            return 0;
        }
        RECT rc;
        GetClientRect(hwnd, &rc);

        scrollOffset -= GET_WHEEL_DELTA_WPARAM(wParam) / 2;

        int maxScroll = GetMaxScroll(rc.bottom, menu.size());

        if (scrollOffset < 0) scrollOffset = 0;
        if (scrollOffset > maxScroll) scrollOffset = maxScroll;

        UpdateScrollBar(hwnd);
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_VSCROLL:
    {     if(isCartOpen){
            SendMessage(borderTable, WM_VSCROLL, wParam, lParam);
            return 0;
        }

        SCROLLINFO si{};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hwnd, SB_VERT, &si);

        int maxScroll = GetMaxScroll(si.nPage, menu.size());

        switch (LOWORD(wParam)) {
        case SB_LINEUP: scrollOffset -= 40; break;
        case SB_LINEDOWN: scrollOffset += 40; break;
        case SB_PAGEUP: scrollOffset -= 150; break;
        case SB_PAGEDOWN: scrollOffset += 150; break;
        case SB_THUMBTRACK: scrollOffset = si.nTrackPos; break;
        }

        if (scrollOffset < 0) scrollOffset = 0;
        if (scrollOffset > maxScroll) scrollOffset = maxScroll;

        si.nPos = scrollOffset;
        SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_COMMAND:
    {
        int id = LOWORD(wParam);

      
        if (id == BTN_CART) {
            isCartOpen = true;
            
            showCartPage(hwnd);   //เรียกหน้า cart

            ShowWindow(hCartButton, SW_HIDE);   //ซ่อนปุ่ม cart

            ShowScrollBar(hwnd, SB_VERT, FALSE);

            // ซ่อนปุ่ม Add ของ menu
            for(int i = 0; i < addButtons.size(); i++){
                ShowWindow(addButtons[i], SW_HIDE);   // [เพิ่ม]
            }

            InvalidateRect(hwnd, NULL, TRUE);
        }
         else if (id >= BTN_ADD_BASE &&
                 id < BTN_ADD_BASE + (int)menu.size())
        {
            int index = id - BTN_ADD_BASE;

            cartSystem.addToCart(menu[index]);

            std::wstring msg =
                L"Added: " + menu[index].name;

            MessageBoxW(hwnd, msg.c_str(),
                        L"Cart", MB_OK);
        }
        else cartCommand(hwnd, wParam);
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rc;
        GetClientRect(hwnd, &rc);

        if(!isCartOpen){
            DrawMenu(hwnd, hdc, rc);
        }


        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ================= CREATE WINDOW =================
HWND CreateMenuWindow(HINSTANCE hInstance)
{
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MenuWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        L"MenuWindow",
        L"Restaurant Menu",
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1400, 900,
        NULL, NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, SW_MAXIMIZE);
    UpdateWindow(hwnd);

    return hwnd;
}
void showMenuPage(HWND hwnd)
{
    isCartOpen = false;
    hideCartPage();

    ShowScrollBar(hwnd, SB_VERT, TRUE);

    ShowWindow(hCartButton, SW_SHOW);

    for(int i = 0; i < addButtons.size(); i++){
        ShowWindow(addButtons[i], SW_SHOW);
    }

    InvalidateRect(hwnd, NULL, TRUE);
}