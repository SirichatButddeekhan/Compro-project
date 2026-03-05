#include <vector>
#include <string>
#include "menu.h"
using namespace std;

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
        void addToCart(MenuItem);
        void removeFromCart(int);
        double calculate();
        vector<CartItem>& getCart(); //สำหรับ GUI
};