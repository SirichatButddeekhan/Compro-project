#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "cart_service.h"
using namespace std;

int main(){
    
    CartSystem item;

    item.loadMenu("MenuItem.txt");
    item.ShowMenuForTest(); //แสดงเมนูสำหรับทดสอบระบบเฉยๆ
    int choice; //ตัวแปรไว้รับค่าที่ผู้ใช้จะเลือก
    while(true){
        cout << "Choose Menu (Select 0 for end program)";
        cin >> choice;
        if(choice == 0) break;
        item.addToCart(choice); //ใช้ฟังก์ชันเพิ่มลงตะกร้า
    }
    char ans;
    cout << "Do you want receipt (enter Y for Yes and N for Not)\n";
    cin >> ans;
    while(true){
        if(ans == 'Y'){
            item.ShowReceipt(); //แสดงใบจองสินค้า
            break;
        }
        else if(ans == 'N'){
            cout << "Good bye\n";
            break;
        }
        else{
            cout << "Invalid input\n";
            cin >> ans;
        }
    }

    return 0;
}