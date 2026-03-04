#include <windows.h>
#include "cart_service.h"

/*//main window setup
void InitApplication(HINSTANCE hInstance);
HWND InitMainWindow(HINSTANCE hInstance, int nCmdShow);*/

//class ของการจัดการหน้า
class PageManage { 
    private:
        int currentPage;
    public:
        int menu_page = 0;
        int cart_page = 1;
        PageManage();
        void setPage(int);
        int getPage();
};

//struct สร้างตาราง
struct CartTable {
    HWND textId;
    HWND textName;
    HWND buttonMinus;
    HWND textQty;
    HWND buttonPlus;
    HWND textTotal;
};

void startCartPage(HWND); //สร้างหน้า cart
void showMenuPage();
void showCartPage(HWND);

void resizeControl(HWND, int, int);

void clearCartRows();
void showCartItem(HWND);

void showReceipt(HWND);

LRESULT CALLBACK BorderProc(HWND, UINT, WPARAM, LPARAM); //ของ cart เอาไว้แปลงปุ่ม + - ให้ใช้ได้

LRESULT CALLBACK ReceiptProc(HWND, UINT, WPARAM, LPARAM); //ของใบเสร็จสำหรับสร้าง window ใหม่

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //ของ window หลัก