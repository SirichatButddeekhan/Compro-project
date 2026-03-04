#include <windows.h>
#include "MenuService.h"
Menu g_menu;
HWND g_edit = NULL;




/* This is where all the input to the window goes to */
HWND textfield,button,textbox,creat_1,read_2,update_3,delete_4;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE: {
    INT_PTR mode = (INT_PTR)((CREATESTRUCT*)lParam)->lpCreateParams;

    // ถ้าเป็นหน้าต่าง CREATE MENU (ถูกส่งมาจาก (LPVOID)1)
    if (mode == 1) {
		CreateWindow("STATIC", "Enter ID:",
            WS_VISIBLE | WS_CHILD,
            20, 0, 120, 20,
            hwnd, NULL, NULL, NULL);

        g_edit = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 20, 300, 25,
            hwnd, (HMENU)100, NULL, NULL);
        CreateWindow("STATIC", "Enter name:",
            WS_VISIBLE | WS_CHILD,
            20, 40, 120, 20,
            hwnd, NULL, NULL, NULL);

        g_edit = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 60, 300, 25,
            hwnd, (HMENU)100, NULL, NULL);

		CreateWindow("STATIC", "Enter Price:",
            WS_VISIBLE | WS_CHILD,
            20, 80, 120, 20,
            hwnd, NULL, NULL, NULL);

        g_edit = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 100, 300, 25,
            hwnd, (HMENU)100, NULL, NULL);

        CreateWindow("BUTTON","CREATE",WS_VISIBLE | WS_CHILD | WS_BORDER,
        20, 130, 100, 25,
        hwnd, NULL, NULL, NULL);
        break;
    }
    if (mode == 2) {
		CreateWindow("STATIC", "This is list of menu ",
            WS_VISIBLE | WS_CHILD,
            100, 20, 200, 50,
            hwnd, NULL, NULL, NULL);
        

        break;

        }
    if (mode == 3) {
		CreateWindow("STATIC", "ENTER ID THAT YOU WANT TO UPDATE ",
            WS_VISIBLE | WS_CHILD,
            20, 20,300, 50,
            hwnd, NULL, NULL, NULL);
        g_edit = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 50, 300, 25,
            hwnd, (HMENU)100, NULL, NULL);
        CreateWindow("STATIC", "NEW NAME ",
            WS_VISIBLE | WS_CHILD,
            20, 80,300, 50,
            hwnd, NULL, NULL, NULL);
        g_edit = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 110, 300, 25,
            hwnd, (HMENU)100, NULL, NULL);
        CreateWindow("STATIC", "NEW PRICE ",
            WS_VISIBLE | WS_CHILD,
            20, 140,300, 50,
            hwnd, NULL, NULL, NULL);
        g_edit = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 170, 300, 25,
            hwnd, (HMENU)100, NULL, NULL);
        CreateWindow("BUTTON","SAVE",WS_VISIBLE | WS_CHILD | WS_BORDER,
        120, 200, 100, 25,
        hwnd, NULL, NULL, NULL);

        break;

        }

    if (mode == 4) {
		CreateWindow("STATIC", "ID THAT YOU WANT TO DELETE ",
            WS_VISIBLE | WS_CHILD,
            20, 20,300, 50,
            hwnd, NULL, NULL, NULL);
        g_edit = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 50, 300, 25,
            hwnd, (HMENU)100, NULL, NULL);
        CreateWindow("BUTTON","DELETE",WS_VISIBLE | WS_CHILD | WS_BORDER,
        120, 80, 100, 25,
        hwnd, NULL, NULL, NULL);

        break;

        }

    // ===== หน้าหลัก (ของเดิม) =====
    textfield = CreateWindow("STATIC","WELCOME TO CRUD APPLICATION",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        (1920 - 250)/2, (1080/2) - 120, 250, 30,
        hwnd,NULL,NULL,NULL);

    CreateWindow("BUTTON","CREATE",WS_VISIBLE | WS_CHILD | WS_BORDER,
        (1920 - 200)/2, (1080/2) - 60, 200, 30,
        hwnd, (HMENU)1, NULL, NULL);

    CreateWindow("BUTTON","READ",WS_VISIBLE | WS_CHILD | WS_BORDER,
        (1920 - 200)/2, (1080/2) - 10, 200, 30,
        hwnd, (HMENU)2, NULL, NULL);

    CreateWindow("BUTTON","UPDATE",WS_VISIBLE | WS_CHILD | WS_BORDER,
        (1920 - 200)/2, (1080/2) + 40, 200, 30,
        hwnd, (HMENU)3, NULL, NULL);

    CreateWindow("BUTTON","DELETE",WS_VISIBLE | WS_CHILD | WS_BORDER,
        (1920 - 200)/2, (1080/2) + 90, 200, 30,
        hwnd, (HMENU)4, NULL, NULL);

    break;
}

	case WM_COMMAND:
    switch (LOWORD(wParam)) {
        case 1:
            
            creat_1 =     CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "WindowClass",
                "CREATE MENU",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                300, 200, 500, 400,
                NULL, NULL,
                GetModuleHandle(NULL),
                (LPVOID)1
            );
            break;
        case 2:

        read_2 = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            "WindowClass",
            "READ MENU",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            300, 200, 500, 400,
            NULL, NULL,
            GetModuleHandle(NULL),
            (LPVOID)2
        );
            break;
        case 3:
        update_3 = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            "WindowClass",
            "DELETE",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            300, 200, 500, 400,
            NULL, NULL,
            GetModuleHandle(NULL),
            (LPVOID)3
        );


            break;
        case 4:
        delete_4 = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            "WindowClass",
            "DELETE",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            300, 200, 500, 400,
            NULL, NULL,
            GetModuleHandle(NULL),
            (LPVOID)4
        );


            break;
    }
    break;
			
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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","CRUD APPLICATION",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		1920, /* width */
		1080, /* height */
		NULL,NULL,hInstance,NULL);
        ShowWindow(hwnd,SW_MAXIMIZE);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
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