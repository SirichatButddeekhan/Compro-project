#include "login.h"
#include "filemanager.h"
#include <string>
#include "menu.h"
#include "crud.h"
using namespace std;

#define BTN_OK 1001 // รหัสสำหรับปุ่มยืนยัน
#define EDIT_USERNAME 2001 // รหัสสำหรับช่องกรอกชื่อผู้ใช้
#define EDIT_PASSWORD 2002  // รหัสสำหรับช่องกรอกรหัสผ่าน

HWND hEditusername, hEditpassword, hLabelUser, hLabelPass, hButton;
//ตัวแปรสำหรับจัดการกับคอนโทรลต่างๆ ในหน้าต่างล็อกอิน

// ฟังก์ชันสำหรับจัดการข้อความของหน้าต่างล็อกอิน(หน้าเเรก)
LRESULT CALLBACK LoginProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch(msg)
    {
    case WM_CREATE:
         //ป้ายชื่อ user
        hLabelUser = CreateWindowExW(0, L"STATIC", L"Username:", 
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE, 0,0,0,0,
            hwnd, NULL, GetModuleHandle(NULL), NULL);
           
            //ป้ายชื่อ password
        hLabelPass = CreateWindowExW(0, L"STATIC", L"Password:",
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE, 0,0,0,0,
            hwnd, NULL, GetModuleHandle(NULL), NULL);
            
            //ช่องกรอกชื่อผู้ใช้
        hEditusername = CreateWindowExW(
            WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            0,0,0,0,
            hwnd, (HMENU)EDIT_USERNAME,
            GetModuleHandle(NULL), NULL);

            //ช่องกรอกรหัสผ่าน
        hEditpassword = CreateWindowExW(
            WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_PASSWORD,
            0,0,0,0,
            hwnd, (HMENU)EDIT_PASSWORD,
            GetModuleHandle(NULL), NULL);
   
            //ปุ่มยืนยัน
        hButton = CreateWindowExW(
            0, L"BUTTON", L"Confirm",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            0,0,0,0,
            hwnd, (HMENU)BTN_OK,
            GetModuleHandle(NULL), NULL);

        return 0;

    case WM_COMMAND:

        if (LOWORD(wParam) == BTN_OK) //ถ้ากดปุ่มยืนยัน
        {
            wchar_t wuser[100], wpass[100]; //ตัวแปรเก็บค่าที่ user and password

            // เอาค่าที่กรอกในช่อง username และ password มาเก็บในตัวแปร wuser และ wpass
            GetWindowTextW(hEditusername, wuser, 100);
            GetWindowTextW(hEditpassword, wpass, 100);

            //แปลงค่า  
            string user(wuser, wuser + wcslen(wuser));
            string pass(wpass, wpass + wcslen(wpass));

            if (user == "admin123" && pass == "555")
            {
                MessageBoxW(hwnd, L"Admin Login Success!", L"Success", MB_OK);
                createaccountadmin(GetModuleHandle(NULL), hwnd);

                ShowWindow(hwnd, SW_HIDE);
                return 0;

                
            }
            else if (checkLogin(user, pass))
            {
                MessageBoxW(hwnd, L"User Login Success!", L"Success", MB_OK);
                CreateMenuWindow(GetModuleHandle(NULL));
                ShowWindow(hwnd, SW_HIDE);
            }
            else
            {
                MessageBoxW(hwnd, L"Login Failed!", L"Failed", MB_OK);
                
            }
        }
        return 0;

    case WM_SIZE:
    {
        int windowWidth = LOWORD(lParam);
        int windowHeight = HIWORD(lParam);

        int labelWidth = 80;
        int editWidth = 250;
        int spacing = 10;

        int totalWidth = labelWidth + spacing + editWidth;
        int startX = (windowWidth - totalWidth) / 2;
        int startY = windowHeight / 3;

        MoveWindow(hLabelUser, startX, startY, labelWidth, 25, TRUE);
        MoveWindow(hEditusername, startX + labelWidth + spacing, startY, editWidth, 25, TRUE);

        MoveWindow(hLabelPass, startX, startY + 50, labelWidth, 25, TRUE);
        MoveWindow(hEditpassword, startX + labelWidth + spacing, startY + 50, editWidth, 25, TRUE);

        MoveWindow(hButton, (windowWidth - 100)/2, startY + 100, 100, 30, TRUE);

        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

HWND CreateLoginWindow(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = LoginProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255,240,205));

    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
        0, L"MyWindow", L"LOGIN",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_MAXIMIZE);
    UpdateWindow(hwnd);

    return hwnd;
}
