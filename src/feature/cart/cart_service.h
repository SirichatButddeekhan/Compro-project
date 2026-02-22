#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
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

//ระบบต่างๆรถเข็น
class CartSystem{
    private:
        vector<MenuItem> menu;
        vector<CartItem> cart;
    public:
        void loadMenu(string);
        void ShowMenuForTest(); //แสดงเมนูสำหรับทดสอบโค้ดเฉยๆ
        void addToCart(int);
        void removeFromCart(int);
        double calculate();
        void ShowCart();
        void ShowReceipt();
};

//ฟังก์ชันโหลดเมนูจากไฟล์
void CartSystem::loadMenu(string file){
    ifstream source(file);
    string textline;
    while(getline(source,textline)){
        stringstream s(textline);
        string temp;
        MenuItem m;

        //นำเข้าข้อมูลเลขเมนู
        getline(s, temp, ',');
        m.id = stoi(temp);
        
        //นำเข้าข้อมูลชื่อเมนู
        getline(s,m.name, ',');
        
        //นำเข้าข้อมูลราคา
        getline(s, temp, ',');
        m.price = stod(temp);
        
        //นำเข้าข้อมูลขายอยู่ไหม
        getline(s,temp,',');
        if(temp == "true") m.available = true;
        else m.available = false;
        
        //นำเข้าข้อมูลคำอธิบาย
        getline(s,m.descripstion,',');

        menu.push_back(m);
    }
    source.close();
}

//ฟังก์ชันแสดงเมนุสำหรับทดสอบ
void CartSystem::ShowMenuForTest(){
    cout << "------------------------------ MENU ------------------------------\n";
    //ส่วนหัวคอลัมป์
        cout << left << setw(4) << "ID";
        cout << "| " << left << setw(15) << "Name";
        cout << "| " << left << setw(8) << "Price";
        cout << "| " << left << setw(12) << "Stat";
        cout << "| " << left << setw(20) << "Descripstion" << endl;
        cout << "------------------------------------------------------------------\n";
    for(int i = 0; i < menu.size(); i++){
        //ข้อมูลข้างใน
        cout << left << setw(4) << menu[i].id;
        cout << "| " << left << setw(15) << menu[i].name; 
        cout << "| " << left << setw(8) << fixed << setprecision(2) << menu[i].price;
        if(menu[i].available) cout << "| " << left << setw(12) << "Available"; //เช็คว่ามีอยู่มั้ย
        else cout << "| " << left << setw(12) << "Sold out";
        cout << "| " << left << setw(20) << menu[i].descripstion << endl;
    }
    cout << "------------------------------------------------------------------\n";
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
                    cout << menu[i].name << " + 1\n";
                    return;
                }
            }
            cart.push_back({menu[i],1}); //เพิ่มเมนูนั้นลงรถเข็น
            cout << "Add " << menu[i].name << " to cart.\n";
            return;
        }
    }
    cout << "Menu not found.\n";
}

//ฟังก์ชันลบออกจากรถเข็น
void CartSystem::removeFromCart(int id){
    cout << "Not yet\n";
}

//ฟังก์ชันคำนวณราคา
double CartSystem::calculate(){
    int sum = 0;
    return sum;
}

//ฟังก์ชันแสดงของในรถเข็น
void CartSystem::ShowCart(){
    cout << "----------\n";
}

//ฟังก์ชันแสดงใบจอง
void CartSystem::ShowReceipt(){
    cout << "HAHA\n";
}