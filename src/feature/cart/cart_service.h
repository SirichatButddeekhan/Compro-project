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
    private:
        vector<MenuItem> menu;
        vector<CartItem> cart;
    public:
        void loadMenu(string);
        void ShowMenuForTest(); //แสดงเมนูสำหรับทดสอบโค้ดเฉยๆ
        void addToCart(int id);
        double calcutale();
        void ShowReceipt();
};

//ฟังก์ชันโหลดเมนูจากไฟล์
void CartSystem::loadMenu(string){

}

//ฟังก์ชันแสดงเมนุสำหรับทดสอบ
void ShowMenuForTest(){

}

//ฟังก์ชันเพิ่มลงรถเข็น
void CartSystem::addToCart(int id){
    for(int i = 0; i < menu.size(); i++){
        if(menu[i].id == id){
            if(!menu[i].available){ //เช็คว่าเมนูยังเปิดขายอยู่มั้ย
                cout << "Sold out\n";
                return;
            }
            for(int i = 0; i < cart.size(); i++){ //เช็คว่ามีเมนูนี้ในรถเข็นอยู่แล้วรึป่าว
                if(cart[i].item.id == id){
                    cart[i].quantity++;
                    cout << "Menu + 1\n";
                    return;
                }
            }
            cart.push_back({menu[i],1}); //เพิ่มเมนูนั้นลงรถเข็น
            return;
        }
        cout << "Menu not found.\n";
    }
}