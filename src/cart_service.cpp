#include <stdio.h>
#include <iomanip>
#include <sstream>
#include "cart_service.h"



//ระบบ cart system-----------------------------------------------------------------
void CartSystem::addToCart(MenuItem m){ //เพิ่มลง cart
    for(int i = 0; i < cart.size(); i++){
        if(cart[i].item.id == m.id){ //เช็คว่ามีอยู่แล้วรึป่าว
            cart[i].quantity++; //มีอยู่แล้วให้ +1
            return;
        }
    }
    CartItem newItem;
    newItem.item = m;
    newItem.quantity = 1;
    cart.push_back(newItem); //ยังไม่มีเพิ่มขึ้นมาใหม่
}

void CartSystem::removeFromCart(int id){ //ลบออกจาก cart
    for(int i = 0; i < cart.size(); i++){
        if(cart[i].item.id == id){
            cart[i].quantity--;
            if(cart[i].quantity == 0){
                cart.erase(cart.begin()+i);
            }
            return;
        }
    }
}

double CartSystem::calculate(){ //คำนวณราคารวมทั้งหมด
    double sum = 0;
    for(int i = 0; i < cart.size(); i++){
        sum += cart[i].item.price * cart[i].quantity;
    }
    return sum;
}

vector<CartItem>& CartSystem::getCart(){ //เรียกตะกร้ามา
    return cart;
}
//--------------------------------------------------------------------------------
