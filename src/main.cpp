#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "login.h"
// ./AAA_TEST.exe
//g++ main.cpp menu.cpp menu_ser.cpp cart_ui.cpp cart_service.cpp crud.cpp filemanager.cpp login.cpp -municode -mwindows -o AAA_TEST.exe
int WINAPI wWinMain( // ปรับเป็น wWinMain เพื่อรองรับ Unicode
    HINSTANCE hInstance,
    HINSTANCE,
    LPWSTR,
    int nCmdShow
)
{
    CreateLoginWindow(hInstance, nCmdShow); 
    // เรียกฟังก์ชันสร้างหน้าต่างล็อกอิน จาก login.h


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) { // ลูปข้อความหลักของแอปพลิเคชัน
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}