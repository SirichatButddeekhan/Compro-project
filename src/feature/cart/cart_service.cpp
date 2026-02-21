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
    int choice;
    while(true){
        cout << "Choose Menu (Select 0 for end program)";
        cin >> choice;
        if(choice == 0) break;
        item.addToCart(choice);
    }
    item.ShowReceipt();

    return 0;
}