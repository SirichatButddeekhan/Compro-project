#include <windows.h>
#include <vector>
#include <string>
using namespace std;

//Data base Menu
struct MenuItem{
    int id;
    wstring name;
    double price;
};

//ตัวแปรใน Cart
class CartItem{
    public:
        MenuItem item;
        int quantity;
};

//ระบบต่างๆรถเข็น
class CartSystem{
    private:
        vector<MenuItem> menu;
        vector<CartItem> cart;
    public:
        void loadMenu(string);
        void addToCart(MenuItem);
        void removeFromCart(int);
        double calculate();
        vector<CartItem>& getCart(); //สำหรับ GUI
        CartSystem();
};

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

void startMenuPage(HWND);
void startCartPage(HWND);

void showMenuPage();
void showCartPage(HWND);

void resizeControl(HWND, int, int);

void clearCartRows();
void showCartItem(HWND);

void showReceipt(HWND);