#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct MenuItem{
    int id;
    string name;
    double price;
    bool available;
    string descripstion;
};

struct CartItem{
    MenuItem item;
    int quantity;
};

void addToCart(vector<CartItem> &cart, MenuItem menu){
    if(!menu.available){
        cout << "Sold out";
        return;
    }

    for(int i = 0; i < cart.size(); i++){
        if(cart[i].item.id == menu.id){
            cart[i].quantity++;
            cout << "Menu +1";
            return;
        }
    }

    cart.push_back({menu,1});
}

int main(){
    

    return 0;
}