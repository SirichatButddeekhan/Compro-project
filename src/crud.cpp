#include <string>
#include <windows.h>
#include "menu.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

Menu g_menu;

HWND hIdEdit = NULL;
HWND hNameEdit = NULL;
HWND hPriceEdit = NULL;
HWND hDelIdEdit = NULL;
HWND textfield,button,textbox,creat_1,read_2,update_3,delete_4;

#define ID_UPD_ID_EDIT     301
#define ID_UPD_NAME_EDIT   302
#define ID_UPD_PRICE_EDIT  303
#define BTN_UPDATE_OK      304
#define BTN_DELETE_OK      405

#define ID_EDIT_ID       201
#define ID_EDIT_NAME     202
#define ID_EDIT_PRICE    203

#define BTN_CREATE       10
HWND hUpdIdEdit=NULL, hUpdNameEdit=NULL, hUpdPriceEdit=NULL;

LRESULT CALLBACK CrudWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){

switch(Message) {

case WM_CREATE:
{
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    int centerX = screenW / 2;
    int centerY = screenH / 2;

    INT_PTR mode = (INT_PTR)((CREATESTRUCT*)lParam)->lpCreateParams;
    

    if (mode == 1) {

        CreateWindowW(L"STATIC", L"Enter ID:", WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
            centerX-150, centerY-120, 120, 20, hwnd, NULL, NULL, NULL);

        hIdEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            centerX-150, centerY-100, 300, 25, hwnd, (HMENU)ID_EDIT_ID, NULL, NULL);

        CreateWindowW(L"STATIC", L"Enter Name:", WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
            centerX-150, centerY-70, 120, 20, hwnd, NULL, NULL, NULL);

        hNameEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            centerX-150, centerY-50, 300, 25, hwnd, (HMENU)ID_EDIT_NAME, NULL, NULL);

        CreateWindowW(L"STATIC", L"Enter Price:", WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
            centerX-150, centerY-20, 120, 20, hwnd, NULL, NULL, NULL);

        hPriceEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            centerX-150, centerY, 300, 25, hwnd, (HMENU)ID_EDIT_PRICE, NULL, NULL);

        CreateWindowW(L"BUTTON", L"CREATE", WS_CHILD | WS_VISIBLE,
            centerX-150, centerY+40, 100, 30, hwnd, (HMENU)BTN_CREATE, NULL, NULL);

        break;
    }

    if (mode == 2) {
        CreateWindowW(L"STATIC", L"This is list of menu ",
            WS_VISIBLE | WS_CHILD,
            centerX-100, centerY-200, 200, 50,
            hwnd, NULL, NULL, NULL);
        break;
    }

    if (mode == 3) {

        CreateWindowW(L"STATIC",L"Enter ID to update:", WS_CHILD|WS_VISIBLE|SS_CENTERIMAGE,
            centerX-150,centerY-120,150,20, hwnd,NULL,NULL,NULL);

        hUpdIdEdit = CreateWindowW(L"EDIT",L"", WS_CHILD|WS_VISIBLE|WS_BORDER,
            centerX-150,centerY-100,300,25, hwnd,(HMENU)ID_UPD_ID_EDIT,NULL,NULL);

        CreateWindowW(L"STATIC",L"New Name:", WS_CHILD|WS_VISIBLE|SS_CENTERIMAGE,
            centerX-150,centerY-70,150,20, hwnd,NULL,NULL,NULL);

        hUpdNameEdit = CreateWindowW(L"EDIT",L"", WS_CHILD|WS_VISIBLE|WS_BORDER,
            centerX-150,centerY-50,300,25, hwnd,(HMENU)ID_UPD_NAME_EDIT,NULL,NULL);

        CreateWindowW(L"STATIC",L"New Price:", WS_CHILD|WS_VISIBLE|SS_CENTERIMAGE,
            centerX-150,centerY-20,150,20, hwnd,NULL,NULL,NULL);

        hUpdPriceEdit = CreateWindowW(L"EDIT",L"", WS_CHILD|WS_VISIBLE|WS_BORDER,
            centerX-150,centerY,300,25, hwnd,(HMENU)ID_UPD_PRICE_EDIT,NULL,NULL);

        CreateWindowW(L"BUTTON",L"UPDATE", WS_CHILD|WS_VISIBLE,
            centerX-150,centerY+40,100,30, hwnd,(HMENU)BTN_UPDATE_OK,NULL,NULL);

        break;
    }

    if (mode == 4) {

        CreateWindowW(L"STATIC", L"DELETE BY ID:", WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
            20, 50, 120, 20, hwnd, NULL, NULL, NULL);

        hDelIdEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            20, 80, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"DELETE", WS_CHILD | WS_VISIBLE,
            20, 110, 100, 30, hwnd, (HMENU)BTN_DELETE_OK, NULL, NULL);
    }

    textfield = CreateWindowW(L"STATIC",L"WELCOME TO CRUD APPLICATION",
        WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTERIMAGE | SS_CENTER,
        centerX-125, centerY-200, 250, 30,
        hwnd,NULL,NULL,NULL);

    CreateWindowW(L"BUTTON",L"CREATE",WS_VISIBLE | WS_CHILD,
        centerX-100, centerY-120, 200, 30,
        hwnd, (HMENU)1, NULL, NULL);

    CreateWindowW(L"BUTTON",L"READ",WS_VISIBLE | WS_CHILD,
        centerX-100, centerY-70, 200, 30,
        hwnd, (HMENU)2, NULL, NULL);

    CreateWindowW(L"BUTTON",L"UPDATE",WS_VISIBLE | WS_CHILD,
        centerX-100, centerY-20, 200, 30,
        hwnd, (HMENU)3, NULL, NULL);

    CreateWindowW(L"BUTTON",L"DELETE",WS_VISIBLE | WS_CHILD,
        centerX-100, centerY+30, 200, 30,
        hwnd, (HMENU)4, NULL, NULL);

    break;
}

    case WM_COMMAND:
{
    switch (LOWORD(wParam))
    {
    case 1:
{
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    HWND h = CreateWindowExW(
        WS_EX_CLIENTEDGE, L"WindowClass", L"CREATE MENU",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, screenW, screenH,
        NULL, NULL, GetModuleHandle(NULL),
        (LPVOID)1
    );

    ShowWindow(h, SW_MAXIMIZE);
}
break;

    case BTN_CREATE:
    {
        wchar_t bufId[64], bufName[256], bufPrice[64];

        GetWindowTextW(hIdEdit, bufId, 64);
        GetWindowTextW(hNameEdit, bufName, 256);
        GetWindowTextW(hPriceEdit, bufPrice, 64);

        int id = _wtoi(bufId);
        double price = _wtof(bufPrice);
        std::wstring name = bufName;

        if (id <= 0 || name.empty()) {
            MessageBoxW(hwnd, L"Please input valid ID and Name", L"ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        g_menu.LoadCSV("../data/menu.csv");

        if (g_menu.CheckId(id)) {
            MessageBoxW(hwnd, L"ID already exists", L"ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        MenuItem item;
        item.id = id;
        item.name = name;
        item.price = price;

        g_menu.CREATE(item);
        g_menu.SaveCSV("../data/menu.csv");

        SetWindowTextW(hIdEdit, L"");
        SetWindowTextW(hNameEdit, L"");
        SetWindowTextW(hPriceEdit, L"");

        MessageBoxW(hwnd, L"Saved to menu.csv!", L"OK", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case 2:
    {


        g_menu.LoadCSV("../data/menu.csv");

        std::wstring output;

        for (const auto& item : g_menu.m) {
            output += std::to_wstring(item.id);
            output += L" | ";
            output += item.name;
            output += L" | ";
            output += std::to_wstring(item.price);
            output += L"\n";
        }

        if (output.empty()) {
            MessageBoxW(hwnd, L"No data", L"READ", MB_OK);
        }
        else {
            MessageBoxW(hwnd, output.c_str(), L"MENU LIST", MB_OK);
        }

        break;
    }

    case 3:
    {
        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);

        HWND h = CreateWindowExW(
            WS_EX_CLIENTEDGE, L"WindowClass", L"UPDATE MENU",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            0, 0, screenW, screenH,
            NULL, NULL, GetModuleHandle(NULL),
            (LPVOID)3
        );

        ShowWindow(h, SW_MAXIMIZE);
    }
    break;
    case BTN_UPDATE_OK:
    {
        const char* PATH = "../data/menu.csv";
        wchar_t bufId[64], bufName[256], bufPrice[64];

        GetWindowTextW(hUpdIdEdit, bufId, 64);
        GetWindowTextW(hUpdNameEdit, bufName, 256);
        GetWindowTextW(hUpdPriceEdit, bufPrice, 64);

        int uid = _wtoi(bufId);
        double uprice = _wtof(bufPrice);
        std::wstring uname = bufName;

        if (uid <= 0 || uname.empty()) {
            MessageBoxW(hwnd, L"Please input valid ID and New Name", L"ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        g_menu.LoadCSV(PATH);

        if (!g_menu.CheckId(uid)) {
            MessageBoxW(hwnd, L"ID not found", L"ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        MenuItem newItem;
        newItem.id = uid;
        newItem.name = uname;
        newItem.price = uprice;

        g_menu.Update(uid, newItem);
        g_menu.SaveCSV(PATH);

        MessageBoxW(hwnd, L"Update Complete!", L"OK", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case 4:
{


    delete_4 = CreateWindowExW(
        WS_EX_CLIENTEDGE, L"WindowClass", L"DELETE MENU",
        WS_OVERLAPPED| WS_VISIBLE | WS_SYSMENU,
        550, 200, 500, 500,
        NULL, NULL, GetModuleHandle(NULL),
        (LPVOID)4
    );

}

    break;

    case BTN_DELETE_OK:
    {
        const char* PATH = "../data/menu.csv";

        wchar_t bufId[64];
        GetWindowTextW(hDelIdEdit, bufId, 64);
        int did = _wtoi(bufId);

        if (did <= 0) {
            MessageBoxW(hwnd, L"Please input valid ID", L"ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        g_menu.LoadCSV(PATH);

        if (!g_menu.CheckId(did)) {
            MessageBoxW(hwnd, L"ID not found", L"ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        g_menu.Delete(did);
        g_menu.SaveCSV(PATH);

        SetWindowTextW(hDelIdEdit, L"");
        MessageBoxW(hwnd, L"Delete Complete!", L"OK", MB_OK | MB_ICONINFORMATION);
        break;
    }
    }
    break;
}

case WM_DESTROY:
{
    break;
}

default:
    return DefWindowProcW(hwnd, Message, wParam, lParam);
}

return 0;


}

HWND createaccountadmin(HINSTANCE hInstance, HWND owner)
{
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = CrudWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"WindowClass";
    wc.hbrBackground = CreateSolidBrush(RGB(255,240,205));


    RegisterClassW(&wc);

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        0,
        L"WindowClass",
        L"ADMIN CRUD PANEL",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, screenW, screenH,
        owner,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, SW_MAXIMIZE);

    return hwnd;
}