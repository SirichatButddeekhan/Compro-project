#define WIN32_LEAN_AND_MEAN
#define UNICODE
#define _UNICODE
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg){
      case WM_PAINT:{
         PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        TextOutW(
            hdc,
            20, 20,
            L"Hello WinAPI",
            lstrlenW(L"Hello WinAPI")
        );
        EndPaint(hwnd, &ps);
         return 0;
      }

    
    
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;}
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPWSTR,
    int nCmdShow
) {
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
        L"yed",
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