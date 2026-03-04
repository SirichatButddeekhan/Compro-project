#include <windows.h>
#include "account.h"

LRESULT CALLBACK AdminProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK UserProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CreateAdminWindow(HINSTANCE hInstance)
{
    WNDCLASSW wc{};
    wc.lpfnWndProc = AdminProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"AdminWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowW(
        L"AdminWindow",
        L"ADMIN ACCOUNT",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
}

void CreateUserWindow(HINSTANCE hInstance)
{
    WNDCLASSW wc{};
    wc.lpfnWndProc = UserProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"UserWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowW(
        L"UserWindow",
        L"USER ACCOUNT",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
}

LRESULT CALLBACK AdminProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            CreateWindowW(L"STATIC", L"Welcome Admin 🎉",
                WS_CHILD|WS_VISIBLE,
                50,50,200,30,
                hwnd,NULL,NULL,NULL);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd,msg,wParam,lParam);
}

LRESULT CALLBACK UserProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            CreateWindowW(L"STATIC", L"Welcome User 🎉",
                WS_CHILD|WS_VISIBLE,
                50,50,200,30,
                hwnd,NULL,NULL,NULL);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd,msg,wParam,lParam);
}