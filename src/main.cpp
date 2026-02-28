#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define BTN_OK 1001
#define EDIT_USERNAME 2001
#define EDIT_PASSWORD 2002
#include <fstream>
#include <string>
HWND hEditusername, hEditpassword;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg){
        
        case WM_CREATE:
        CreateWindowExW(//กล่องข้อความสำหรับ username



            WS_EX_CLIENTEDGE,     // ขอบสวย ๆ
            L"STATIC",            // ประเภท: ข้อความ
            L"Username:",         // ข้อความเริ่มต้น
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            20, 20,               // ตำแหน่ง
            80, 25,              // ขนาด
            hwnd,
            NULL,
            GetModuleHandle(NULL),
            NULL
        )
        ;
         CreateWindowExW( //กล่องข้อความสำหรับ password



            WS_EX_CLIENTEDGE,     // ขอบสวย ๆ
            L"STATIC",            // ประเภท: ข้อความ
            L"Password:",         // ข้อความเริ่มต้น
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            20, 50,               // ตำแหน่ง
            80, 25,              // ขนาด
            hwnd,
            NULL,
            GetModuleHandle(NULL),
            NULL
        )
        ;
            hEditusername = CreateWindowExW(
            WS_EX_CLIENTEDGE,     // ขอบสวย ๆ
            L"EDIT",              // ประเภท: กล่องข้อความ
            L"",                  // ข้อความเริ่มต้น
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
            100, 20,               // ตำแหน่ง
            250, 25,              // ขนาด
            hwnd,
            NULL,
            GetModuleHandle(NULL),
            NULL
        );
         hEditpassword = CreateWindowExW(
            WS_EX_CLIENTEDGE,     // ขอบสวย ๆ
            L"EDIT",              // ประเภท: กล่องข้อความ
            L"",                  // ข้อความเริ่มต้น
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
            100, 50,               // ตำแหน่ง
            250, 25,              // ขนาด
            hwnd,
            NULL,
            GetModuleHandle(NULL),
            NULL
        );
           CreateWindowExW(
        0,
        L"BUTTON",// ประเภท: ปุ่ม
        L"confirm", // ข้อความบนปุ่ม
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        110, 80, 100, 30, // ตำแหน่งและขนาด
        hwnd, (HMENU)BTN_OK, GetModuleHandle(NULL), NULL
    );
    return 0;
    case WM_COMMAND:
    if (LOWORD(wParam) == BTN_OK) {

        wchar_t user[100];
        wchar_t pass[100];

        GetWindowTextW(hEditusername, user, 100);
        GetWindowTextW(hEditpassword, pass, 100);

        MessageBoxW(
            hwnd,
            user,
            L"คุณกรอก Username คือ",
            MB_OK | MB_ICONINFORMATION
        );
    }
    return 0;
      

    
    
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;}
    
    return DefWindowProc(hwnd, msg, wParam, lParam);}



   int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR     lpCmdLine,
    int       nCmdShow
)
 {
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        L"MyWindow",
        L"LOGIN",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}