#include <windows.h>

class PageManage {
    private:
        int currentPage;
    public:
        int menu_page = 0;
        int cart_page = 1;
        PageManage();
        void setPage(int);
        void getPage();
};

void startMenuPage(HWND);
void startCartPage(HWND);

void showMenuPage();
void showCartPage(HWND);

void resizeControl(HWND, int, int);