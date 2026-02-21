#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//Data base Menu
class MenuItem{
    public:
        int id;
        string name;
        double price;
        bool available;
        string descripstion;
};

//ตัวแปรใน Cart
class CartItem{
    public:
        MenuItem item;
        int quantity;
};

class CartSystem{
    public:
        void addToCart(vector<CartItem> &, MenuItem);
};

//ฟังก์ชันเพิ่มลงรถเข็น
void CartSystem::addToCart(vector<CartItem> &cart, MenuItem menu){
    if(!menu.available){ //เช็คว่าเมนูยังเปิดขายอยู่มั้ย
        cout << "Sold out";
        return;
    }

    for(int i = 0; i < cart.size(); i++){ //เช็คว่ามีเมนูนี้ในรถเข็นอยู่แล้วรึป่าว
        if(cart[i].item.id == menu.id){
            cart[i].quantity++;
            cout << "Menu +1";
            return;
        }
    }

    cart.push_back({menu,1}); //เพิ่มเมนูนั้นลงรถเข็น
}

int main(){
    

    return 0;
}