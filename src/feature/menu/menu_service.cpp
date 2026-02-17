#include<iostream>
#include<string>
using namespace std;

int N;

class Menu{
        int id{};
        string name;
        double price{};
        string category;

    public:
        void showmessage();
        void get_food_name(int );

};


void Menu::showmessage(){
        cout << "1.)ADD MENU : " << endl;
        cout << "2.)DELETE MENU : " << endl;
        cout << "3.)UPDATE MENU : " << endl;
        cout << "4.)EXIT MENU : " << endl;
        cout << "------------------------" << endl;
    }

void Menu::get_food_name(int N){
    if(N=1){
        cout << "Input food name: ";
    }
}







int main(){
    Menu m;
    m.showmessage();
    cout << "Input number :" ;
    cin >> N;
}