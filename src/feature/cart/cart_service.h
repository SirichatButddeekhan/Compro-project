#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
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
    cout << "\n\n------------------------------ MENU ------------------------------\n";
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
        cout << "| " << left << setw(8) << fixed << setprecision(1) << menu[i].price;
        if(menu[i].available) cout << "| " << left << setw(12) << "Available"; //เช็คว่ามีอยู่มั้ย
        else cout << "| " << left << setw(12) << "Sold out";
        cout << "| " << left << setw(20) << menu[i].descripstion << endl;
    }
    cout << "------------------------------------------------------------------\n\n";
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
    for(int i = 0; i < cart.size(); i++){
        if(cart[i].item.id == id){
            cart[i].quantity--;
            if(cart[i].quantity == 0){
                cout << cart[i].item.name << " removed.\n";
                cart.erase(cart.begin() + i);
            }
            else cout << cart[i].item.name << " - 1\n";
            return;
        }
    }
    cout << "This menu not in cart.\n";
}

//ฟังก์ชันคำนวณราคา
double CartSystem::calculate(){
    double sum = 0;
    for(int i = 0; i < cart.size(); i++){
        sum += cart[i].item.price * cart[i].quantity;
    }
    return sum;
}

//ฟังก์ชันแสดงของในรถเข็น
void CartSystem::ShowCart(){
    cout << "\n\n------------------------------ CART ------------------------------\n";
    if(cart.empty()){
        cout << "Cart is empty.\n";
        cout << "------------------------------------------------------------------\n";
        return;
    }
    //ส่วนหัวคอลัมป์
    cout << left << setw(4) << "ID";
    cout << "| " << left << setw(20) << "Name";
    cout << " |" << right << setw(15) << "Amount";
    cout << " |" << right << setw(20) << "Price" << endl;
    //cout << "| " << left << setw(10) << "Total" << endl;
    cout << "------------------------------------------------------------------\n";
    for(int i = 0; i < cart.size(); i++){
        //ข้อมูลข้างใน
        double itemPrice = cart[i].item.price * cart[i].quantity; 
        cout << left << setw(4) << cart[i].item.id;
        cout << "| " << left << setw(20) << cart[i].item.name;
        cout << " |" << right << setw(15) << cart[i].quantity; 
        cout << " |" << right << setw(20) << fixed << setprecision(1) << itemPrice << endl;
    }
    //ส่วนท้ายรวมราคาทั้งหมด
    cout << "------------------------------------------------------------------\n";
    cout << left << setw(4) << " ";
    cout << "  " << left << setw(20) << " ";
    cout << " |" << right << setw(15) << "Total";
    cout << " |" << right << setw(20) << calculate() << endl;
    cout << "------------------------------------------------------------------\n";
}

//ฟังก์ชันแสดงใบจอง
void CartSystem::ShowReceipt(){
    if(cart.empty()){
        cout << "\n\n----------------------------------------------\n";
        cout << "          Cart is empty!! Good bye!!\n";
        cout << "----------------------------------------------\n";
        return;
    }

    int trackId = 10000 + rand()%10;
    int totalQty = 0;
    cout << "\n\n--------------- Purchase Order ---------------\n";
    cout << "Order No. : " << trackId << endl;
    cout << "----------------------------------------------\n";
    
    //ส่วนหัวคอลัมป์
    cout << left << setw(15) << "Name";
    cout << right << setw(5) << "Qty";
    cout << right << setw(14) << "Price";
    cout << right << setw(12) << "Total" << endl;
    cout << "----------------------------------------------\n";
    
    for(int i = 0; i < cart.size(); i++){
        //ข้อมูลข้างใน
        double itemPrice = cart[i].item.price * cart[i].quantity;
        cout << left << setw(15) << cart[i].item.name;
        cout << right << setw(5) << cart[i].quantity;
        cout << right << setw(14) << cart[i].item.price;
        cout << right << setw(12) << fixed << setprecision(2) << itemPrice << endl;
        totalQty += cart[i].quantity;
    }
    //ส่วนท้ายรวมราคาทั้งหมด
    cout << "----------------------------------------------\n";
    cout << left << setw(15) << "Total Quantity";
    cout << right << setw(5) << totalQty;
    cout << right << setw(14) << "GRAND TOTAL";
    cout << right << setw(12) << fixed << setprecision(2) << calculate() << endl;
    cout << "----------------------------------------------\n";
}