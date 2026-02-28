#define WIN32_LEAN_AND_MEAN // g++ main.cpp -municode -mwindows -o app.exe
#include <windows.h> //.\app.exe
#define BTN_OK 1001
#define EDIT_USERNAME 2001 // ตัวแปรสำหรับเก็บรหัสของกล่องข้อความ username
#define EDIT_PASSWORD 2002 // ตัวแปรสำหรับเก็บรหัสของกล่องข้อความ password
#include <fstream>
#include <string>
using namespace std;
HWND hEditusername, hEditpassword; // ตัวแปรสำหรับเก็บ handle ของกล่องข้อความ


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
            WS_CHILD | WS_VISIBLE | SS_LEFT, //
            20, 50,               // ตำแหน่ง
            80, 25,              // ขนาด
            hwnd,
            NULL,
            GetModuleHandle(NULL),
            NULL
        )
        ;
            hEditusername = CreateWindowExW( //input username
            WS_EX_CLIENTEDGE,     // ขอบสวย ๆ
            L"EDIT",              // ประเภท: กล่องข้อความ
            L"",                  // ข้อความเริ่มต้น
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
            100, 20,               // ตำแหน่ง
            250, 25,              // ขนาด
            hwnd,
            (HMENU)EDIT_USERNAME,
            GetModuleHandle(NULL),
            NULL
        );
         hEditpassword = CreateWindowExW(//input password
            WS_EX_CLIENTEDGE,     // ขอบสวย ๆ 
            L"EDIT",              // ประเภท: กล่องข้อความ
            L"",                  // ข้อความเริ่มต้น
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
            100, 50,               // ตำแหน่ง
            250, 25,              // ขนาด
            hwnd,
            (HMENU)EDIT_PASSWORD,
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

        wchar_t wuser[100]; // ตัวแปรสำหรับเก็บข้อความจากกล่อง username 100 ตัว
        wchar_t wpass[100]; // ตัวแปรสำหรับเก็บข้อความจากกล่อง password 100 ตัว

        GetWindowTextW(hEditusername, wuser, 100); //เอาข้อความใน กล่อง user ไปเก็บในตัวแปร wuser
        GetWindowTextW(hEditpassword, wpass, 100); //เอาข้อความใน กล่อง pass ไปเก็บในตัวแปร wpass

// แปลง wchar_t -> string (ภาษาอังกฤษ)
       string user(wuser, wuser + wcslen(wuser));
       string pass(wpass, wpass + wcslen(wpass));



        ifstream file("userandpass.txt"); //เปิดไฟล์ อ่านข้อมูล username และ password
        bool found = false;
        if(!file.is_open()) { //ถ้าเปิดไฟล์ไม่ได้ ให้แสดงข้อความ error
            MessageBoxW(hwnd, L"Could not open userandpass.txt", L"Error", MB_OK | MB_ICONERROR);
            return 0;
        }
        string userline ,passline; //ตัวแปรสำหรับเก็บข้อมูล username และ password ที่อ่านจากไฟล์
        while(file>> userline >> passline) {//อ่านข้อมูลจากไฟล์ทีละบรรทัด จนกว่าจะหมดไฟล์ เก็ขไว้ใน userline เเละ passline
            
            if (user == userline && pass == passline) { //check login
                found = true;
                break;
            }
        }
        file.close();
        if (found) {//ถ้าเจอ username และ password ที่ตรงกันในไฟล์ ให้แสดงข้อความ login success
            MessageBoxW(hwnd, L"Login Success!", L"Success", MB_OK | MB_ICONINFORMATION);
            HWND hAccount = CreateWindowExW(
        0,
        L"AccountWindow",          // class ที่ register ไว้
        L"ACCOUNT",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL,
        GetModuleHandle(NULL),
        NULL 
        );
        ShowWindow(hAccount, SW_SHOW);
        UpdateWindow(hAccount);
        } else {//ถ้าไม่เจอ username และ password ที่ตรงกันในไฟล์ ให้แสดงข้อความ login failed
            MessageBoxW(hwnd, L"Login Failed!", L"Failed", MB_OK | MB_ICONERROR);
        }

       

    }
    return 0;
      

    
    
        case WM_DESTROY: 
            PostQuitMessage(0);
            return 0;}
    
    return DefWindowProc(hwnd, msg, wParam, lParam);} 
    // หน้าต่างสำหรับแสดงข้อความหลังจาก login สำเร็จ
    LRESULT CALLBACK AccountProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindowExW(
                0,
                L"STATIC",
                L"Welcome to your account 🎉",
                WS_CHILD | WS_VISIBLE,
                50, 50, 250, 30,
                hwnd,
                NULL,
                GetModuleHandle(NULL),
                NULL
            );
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}



   int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR     lpCmdLine,
    int       nCmdShow
)

 {
    WNDCLASSEXW wc{}; //กำหนดข้อมูลสำหรับการสร้างหน้าต่าง login
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassExW(&wc); //ลงทะเบียนหน้าต่าง account
   WNDCLASSEXW wc2{};
   wc2.cbSize = sizeof(WNDCLASSEXW);
   wc2.lpfnWndProc = AccountProc;
   wc2.hInstance = hInstance;
   wc2.lpszClassName = L"AccountWindow";
   wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

RegisterClassExW(&wc2);

    HWND hwnd = CreateWindowExW( //สร้างหน้าต่าง login
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
