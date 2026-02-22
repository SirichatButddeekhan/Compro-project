#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include "cart_service.h"
using namespace std;

int main(){
    
    CartSystem item;

    char mode = ' '; //ตัวแปรไว้เก็บเป็นเงื่อนไขโหมดที่ผู้ใช้เลือก
    char choice; //ตัวแปรไว้รับค่าที่ผู้ใช้จะเลือก
    int id; //ตัวแปรเลขสินค้า

    item.loadMenu("MenuItem.txt");
    item.ShowMenuForTest(); //แสดงเมนูสำหรับทดสอบระบบเฉยๆ
    

    while(true){
        //เลือกโหมด หรือถูกย้อนกลับมา 'B'
        if(mode == ' '){
            cout << "------------------------------ MODE ------------------------------\n";
            cout << "[A] Add to cart [D] Remove form cart [C] Open cart [E] Exit\n";
            cout << "Select mode : ";
            cin >> choice;
            choice = toupper(choice);

            if(choice == 'E'){
                cout << "Good bye";
                break;
            }
            if(choice == 'A' || choice == 'D' || choice == 'C'){
                mode = choice;
            }
            else{
                cout << "Invalid input!!\n";
                continue;
            }
        }
        //mode add to cart 'A'
        else if(mode == 'A'){
            cout << "--------------- ADD TO CART MODE ---------------\n";
            cout << "Enter menu id ([B] to back) : ";
            cin >> choice;
            if(choice == 'B'){
                mode = ' ';
                continue;
            }
            cin.putback(choice);
            cin >> id;

            item.addToCart(id);
        }
        //mode remove to cart 'D'
        else if(mode == 'D'){
            cout << "------------ REMOVE FROM CART MODE ------------\n";
            cout << "Enter menu id ([B] to back) : ";
            cin >> choice;
            if(choice == 'B'){
                mode = ' ';
                continue;
            }
            cin.putback(choice);
            cin >> id;

            item.removeFromCart(id);
        }
        //mode open cart 'C'
        else if(mode == 'C'){
            cout << "----------------- CART MODE -----------------\n";
            item.ShowCart();
            cout << "Select [R] Show Receipt [B] back : ";
            cin >> choice;
            choice = toupper(choice);
            if(choice == 'R'){
                item.ShowReceipt();
                break;
            }
            else if(choice == 'B'){
                mode = ' ';
                continue;
            }
            else cout << "Invalid input!!\n";
        }
    }

    return 0;
}