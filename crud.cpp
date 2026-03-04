#include <string>
#include <windows.h>
#include "MenuService.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

Menu g_menu;
HWND g_edit = NULL;
HWND hIdEdit = NULL;
HWND hNameEdit = NULL;
HWND hPriceEdit = NULL;
HWND hDelIdEdit = NULL;
#define ID_UPD_ID_EDIT     301
#define ID_UPD_NAME_EDIT   302
#define ID_UPD_PRICE_EDIT  303
#define BTN_UPDATE_OK      304
#define BTN_DELETE_OK 405

// id ของช่อง edit 
#define ID_EDIT_ID       201
#define ID_EDIT_NAME     202
#define ID_EDIT_PRICE    203

// id ของปุ่ม CREATE ภายในหน้าต่าง CREATE 
#define BTN_CREATE       101


/* This is where all the input to the window goes to */
HWND textfield,button,textbox,creat_1,read_2,update_3,delete_4;
HWND hUpdIdEdit=NULL, hUpdNameEdit=NULL, hUpdPriceEdit=NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE: {
    INT_PTR mode = (INT_PTR)((CREATESTRUCT*)lParam)->lpCreateParams;

    if (mode == 1) {
        CreateWindowA("STATIC", "Enter ID:", WS_CHILD | WS_VISIBLE,
            20, 10, 120, 20, hwnd, NULL, NULL, NULL);

        hIdEdit = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            20, 30, 300, 25, hwnd, (HMENU)ID_EDIT_ID, NULL, NULL);

        CreateWindowA("STATIC", "Enter Name:", WS_CHILD | WS_VISIBLE,
            20, 60, 120, 20, hwnd, NULL, NULL, NULL);

        hNameEdit = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            20, 80, 300, 25, hwnd, (HMENU)ID_EDIT_NAME, NULL, NULL);

        CreateWindowA("STATIC", "Enter Price:", WS_CHILD | WS_VISIBLE,
            20, 110, 120, 20, hwnd, NULL, NULL, NULL);

        hPriceEdit = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            20, 130, 300, 25, hwnd, (HMENU)ID_EDIT_PRICE, NULL, NULL);

        CreateWindowA("BUTTON", "CREATE", WS_CHILD | WS_VISIBLE | WS_BORDER,
            20, 170, 100, 30, hwnd, (HMENU)BTN_CREATE, NULL, NULL);

        break; // ✅ ห้าม return
    }

    if (mode == 2) {
		CreateWindow("STATIC", "This is list of menu ",
            WS_VISIBLE | WS_CHILD,
            100, 20, 200, 50,
            hwnd, NULL, NULL, NULL);
        

        break;

        }
    if (mode == 3) {
            CreateWindowA("STATIC","Enter ID to update:", WS_CHILD|WS_VISIBLE, 20,10,150,20, hwnd,NULL,NULL,NULL);
            hUpdIdEdit = CreateWindowA("EDIT","", WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL,
                                    20,30,300,25, hwnd,(HMENU)ID_UPD_ID_EDIT,NULL,NULL);

            CreateWindowA("STATIC","New Name:", WS_CHILD|WS_VISIBLE, 20,60,150,20, hwnd,NULL,NULL,NULL);
            hUpdNameEdit = CreateWindowA("EDIT","", WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL,
                                        20,80,300,25, hwnd,(HMENU)ID_UPD_NAME_EDIT,NULL,NULL);

            CreateWindowA("STATIC","New Price:", WS_CHILD|WS_VISIBLE, 20,110,150,20, hwnd,NULL,NULL,NULL);
            hUpdPriceEdit = CreateWindowA("EDIT","", WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL,
                                        20,130,300,25, hwnd,(HMENU)ID_UPD_PRICE_EDIT,NULL,NULL);

            CreateWindowA("BUTTON","UPDATE", WS_CHILD|WS_VISIBLE|WS_BORDER,
                        20,170,100,30, hwnd,(HMENU)BTN_UPDATE_OK,NULL,NULL);

            break;
        }

    if (mode == 4) {
        CreateWindowA("STATIC", "DELETE BY ID:", WS_CHILD | WS_VISIBLE,
            20, 20, 120, 20, hwnd, NULL, NULL, NULL);

        hDelIdEdit = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            20, 50, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowA("BUTTON", "DELETE", WS_CHILD | WS_VISIBLE,
            20, 90, 100, 30, hwnd, (HMENU)BTN_DELETE_OK, NULL, NULL);
    }

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
{
    switch (LOWORD(wParam))
    {
    case 1:
        CreateWindowExA(
            WS_EX_CLIENTEDGE, "WindowClass", "CREATE MENU",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            300, 200, 500, 300,
            NULL, NULL, GetModuleHandle(NULL),
            (LPVOID)1
        );
        break;

    case BTN_CREATE:
    {
        char bufId[64], bufName[256], bufPrice[64];

        GetWindowTextA(hIdEdit, bufId, 64);
        GetWindowTextA(hNameEdit, bufName, 256);
        GetWindowTextA(hPriceEdit, bufPrice, 64);

        int id = atoi(bufId);
        double price = atof(bufPrice);
        std::string name = bufName;

        if (id <= 0 || name.empty()) {
            MessageBoxA(hwnd, "Please input valid ID and Name", "ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        g_menu.LoadCSV("../data/menu.csv");

        if (g_menu.CheckId(id)) {
            MessageBoxA(hwnd, "ID already exists", "ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        MenuItem item;
        item.id = id;
        item.name = name;
        item.price = price;

        g_menu.CREATE(item);
        g_menu.SaveCSV("../data/menu.csv");

        SetWindowTextA(hIdEdit, "");
        SetWindowTextA(hNameEdit, "");
        SetWindowTextA(hPriceEdit, "");

        MessageBoxA(hwnd, "Saved to menu.csv!", "OK", MB_OK | MB_ICONINFORMATION);
        break;
    }

     case 2:   // READ BUTTON
    {
        g_menu.LoadCSV("../data/menu.csv");

        std::string output;

        for (const auto& item : g_menu.m) {
            output += std::to_string(item.id);
            output += " | ";
            output += item.name;
            output += " | ";
            output += std::to_string(item.price);
            output += "\n";
            }

            if(output.empty()){
                MessageBox(hwnd,"No data","READ",MB_OK);
            }
            else{
                MessageBoxA(hwnd,output.c_str(),"MENU LIST",MB_OK);
            }

            break;
        }

    // ======= ✅ แก้เฉพาะ case 3 + 4 + OK ตามที่คุณต้องการ =======

    case 3:
        CreateWindowExA(
            WS_EX_CLIENTEDGE, "WindowClass", "UPDATE MENU",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            300, 200, 500, 300,
            NULL, NULL, GetModuleHandle(NULL),
            (LPVOID)3
        );
        break;

    case BTN_UPDATE_OK:
    {
        const char* PATH = "../data/menu.csv";
        MessageBoxA(hwnd, "UPDATE BUTTON CLICKED", "DEBUG", MB_OK);

        char bufId[64], bufName[256], bufPrice[64];
        GetWindowTextA(hUpdIdEdit, bufId, 64);
        GetWindowTextA(hUpdNameEdit, bufName, 256);
        GetWindowTextA(hUpdPriceEdit, bufPrice, 64);

        int uid = atoi(bufId);
        double uprice = atof(bufPrice);
        std::string uname = bufName;

        if (uid <= 0 || uname.empty()) {
            MessageBoxA(hwnd, "Please input valid ID and New Name", "ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        g_menu.LoadCSV(PATH);

        if (!g_menu.CheckId(uid)) {
            MessageBoxA(hwnd, "ID not found", "ERROR", MB_OK | MB_ICONWARNING);
            break;
        }

        MenuItem newItem;
        newItem.id = uid;
        newItem.name = uname;
        newItem.price = uprice;

        g_menu.Update(uid, newItem);
        g_menu.SaveCSV(PATH);

        MessageBoxA(hwnd, "Update Complete!", "OK", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case 4:
        delete_4 = CreateWindowExA(
            WS_EX_CLIENTEDGE, "WindowClass", "DELETE MENU",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            300, 200, 500, 300,
            NULL, NULL, GetModuleHandle(NULL),
            (LPVOID)4
        );
        break;

    case BTN_DELETE_OK:
{
    const char* PATH = "../data/menu.csv";

    char bufId[64];
    GetWindowTextA(hDelIdEdit, bufId, 64);
    int did = atoi(bufId);

    if (did <= 0) {
        MessageBoxA(hwnd, "Please input valid ID", "ERROR", MB_OK | MB_ICONWARNING);
        break;
    }

    g_menu.LoadCSV(PATH);

    if (!g_menu.CheckId(did)) {
        MessageBoxA(hwnd, "ID not found", "ERROR", MB_OK | MB_ICONWARNING);
        break;
    }

    g_menu.Delete(did);
    g_menu.SaveCSV(PATH);

    SetWindowTextA(hDelIdEdit, "");
    MessageBoxA(hwnd, "Delete Complete!", "OK", MB_OK | MB_ICONINFORMATION);
    break;
}
    }
    break;
} 
        
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