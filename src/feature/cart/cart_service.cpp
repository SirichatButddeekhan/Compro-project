#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "cart_service.h"
using namespace std;

int main(){

    srand(time(0));
    
    CartSystem item;

    char mode = ' '; //ตัวแปรไว้เก็บเป็นเงื่อนไขโหมดที่ผู้ใช้เลือก
    char choice; //ตัวแปรไว้รับค่าที่ผู้ใช้จะเลือก
    int id; //ตัวแปรเลขสินค้า

    item.loadMenu("MenuItem.txt");

    while(true){
        //เลือกโหมด หรือถูกย้อนกลับมา 'B'
        if(mode == ' '){
            item.ShowMenuForTest(); //แสดงเมนูสำหรับทดสอบระบบเฉยๆ
            cout << "------------------------------ MODE ------------------------------\n";
            cout << "[A] Add to cart | [D] Remove form cart | [C] Open cart | [E] Exit\n";
            cout << "Select mode : ";
            cin >> choice;
            choice = toupper(choice);

            if(choice == 'E'){
                cout << "GOOD BYE!!";
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
            cout << "Enter menu id ([M] Mode [C] Open Cart) : ";
            cin >> choice;
            choice = toupper(choice);
            if(choice == 'M'){
                mode = ' ';
                continue;
            }
            else if(choice == 'C'){
                mode = 'C';
                continue;
            }
            cin.putback(choice);
            cin >> id;

            item.addToCart(id);
        }
        //mode remove to cart 'D'
        else if(mode == 'D'){
            cout << "------------ REMOVE FROM CART MODE ------------\n";
            cout << "Enter menu id ([M] Mode [C] Open Cart) : ";
            cin >> choice;
            choice = toupper(choice);
            if(choice == 'M'){
                mode = ' ';
                continue;
            }
            else if(choice == 'C'){
                mode = 'C';
                continue;
            }
            cin.putback(choice);
            cin >> id;

            item.removeFromCart(id);
        }
        //mode open cart 'C'
        else if(mode == 'C'){
            item.ShowCart();
            cout << "Select [A] Add item | [D] Remove item | [R] Show Receipt and exit | [M] Mode : ";
            cin >> choice;
            choice = toupper(choice);
            if(choice == 'R'){
                item.ShowReceipt();
                break;
            }
            else if(choice == 'A'){
                item.ShowMenuForTest(); //แสดงเมนูสำหรับทดสอบระบบเฉยๆ
                mode = 'A';
                continue;
            }
            else if(choice == 'D'){
                mode = 'D';
                continue;
            }
            else if(choice == 'M'){
                mode = ' ';
                continue;
            }
            else cout << "Invalid input!!\n";
        }
    }

    return 0;
}