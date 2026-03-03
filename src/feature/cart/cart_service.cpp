#include <windows.h>
#include <stdio.h>
#include "cart_service.h"

HWND textTitleMenu, buttonShowCart;
HWND textCart, buttonBack_cart;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
       
        case WM_CREATE: {
            textTitleMenu = CreateWindowW(L"STATIC",L"MENU SYSTEM",WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE,
                0,0,300,50,
                hwnd,NULL,NULL,NULL);

            buttonShowCart = CreateWindowW(L"BUTTON",L"Show Cart",WS_VISIBLE|WS_CHILD|WS_BORDER,
                0,0,200,50,
                hwnd,(HMENU) 1,NULL,NULL);
           
            break;
        }

        case WM_SIZE: { //ฟังก์ชันไว้จัดขนาดของปุ่มต่างๆให้เป็นไปตามที่ต้องการแม้จะย่อขยาย
            int window_width = LOWORD(lParam);
            int window_height = HIWORD(lParam);

            int textBox_x = (window_width - 300)/2; //จัดขาดให้อยู่ตรงกลางตามแกน x ซึ่งจะทำการเอาขนาดจอ - ขนาดกล่องข้อความ/ปุ่ม
            int textBox_y = 50; //จัดขาดตามแกน y ให้มันต่ำกว่าข้างบนลงมา 50 จากขนาด 1600:900
            int button_x = (window_width - 200)/2; //จัดขาดให้อยู่ตรงกลางตามแกน x ซึ่งจะทำการเอาขนาดจอ - ขนาดกล่องข้อความ/ปุ่ม
            int button_y = 110;

            MoveWindow(textTitleMenu,textBox_x,textBox_y,300,50,TRUE);
            MoveWindow(buttonShowCart, button_x, button_y, 200, 50, TRUE);
        }

        case WM_COMMAND: {

            switch (LOWORD(wParam)){
                case 1: {

                    break;
                }
            }

            break;
        }

        /* Upon destruction, tell the main thread to stop */
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
       
        /* All other messages (a lot of them) are processed using default procedures */
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc; /* A properties struct of our window */
    HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
    MSG msg; /* A temporary location for all messages */

    /* zero out the struct and set the stuff we want to modify */
    memset(&wc,0,sizeof(wc));
    wc.cbSize    = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc; /* This is where we will send messages to */
    wc.hInstance     = hInstance;
    wc.hCursor   = LoadCursor(NULL, IDC_ARROW);
   
    /* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
    wc.hbrBackground = CreateSolidBrush(RGB(150,175,220));
    wc.lpszClassName = L"WindowClass";
    wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
    wc.hIconSm   = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

    if(!RegisterClassExW(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!",L"Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowExW(WS_EX_CLIENTEDGE,L"WindowClass",L"Open Program", WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, /* x */
        CW_USEDEFAULT, /* y */
        800, /* width */
        450, /* height */
        NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd, SW_MAXIMIZE);
    UpdateWindow(hwnd);

    if(hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!",L"Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    /*
        This is the heart of our program where all input is processed and
        sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
        this loop will not produce unreasonably high CPU usage
    */
    while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
        TranslateMessage(&msg); /* Translate key codes to chars if present */
        DispatchMessage(&msg); /* Send it to WndProc */
    }
    return msg.wParam;
}
