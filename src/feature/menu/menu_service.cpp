<<<<<<< Updated upstream
=======
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iomanip>   // ✅ เพิ่มเพื่อจัดคอลัมน์ด้วย setw
using namespace std;

class Menu{
        vector<int> id;
        vector<string>  Name;
        vector<string> category;
        vector<double> price;

    public:
        void showmessage();
        void get_food_name();
        void delete_food();
        void show_menu();
        void update_food();
};

void Menu::showmessage(){
    cout << "------------------------\n";
    cout << "1.)ADD MENU : \n";
    cout << "2.)DELETE MENU : \n";
    cout << "3.)SHOW MENU : \n";   // ✅ เปลี่ยนข้อความให้ตรงกับ main
    cout << "4.)EXIT MENU : \n";
    cout << "------------------------\n";
}

void Menu::get_food_name(){
    string namefood;
    int id_input;
    double price_input;
    string input_category;
    char Con;

    cout << "Input name of food : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ กันปัญหา newline ค้าง
    getline(cin, namefood);

    cout << "ID : ";
    cin >> id_input;

    cout << "Category : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ เคลียร์ newline ก่อน getline
    getline(cin, input_category);

    cout << "Price : ";
    cin >> price_input;

    // ✅ push ลงทุก vector ให้ครบ
    Name.push_back(namefood);
    id.push_back(id_input);
    category.push_back(input_category);
    price.push_back(price_input);

    cout << "Added: " << namefood << "!!!!\n";
    cout << "You want to see list of food? (Y/N): ";
    cin >> Con;
    if(Con == 'Y' || Con == 'y') show_menu();
}

void Menu::show_menu(){
    if(Name.empty()){
        cout << "\n[Menu is empty]\n\n";
        return;
    }

    // ✅ หัวตาราง
    cout << "\n==================== MENU LIST =========================\n";
    cout << left
         << setw(8)  << "ID"
         << setw(25) << "NAME"
         << setw(15) << "CATEGORY"
         << right << setw(10) << "PRICE"
         << "\n";

    cout << string(60, '-') << "\n";

    // ✅ ข้อมูล
    for(size_t i = 0; i < Name.size(); i++){
        cout << left
             << setw(8)  << id[i]
             << setw(25) << Name[i]
             << setw(15) << category[i]
             << right << setw(10) << fixed << setprecision(2) << price[i]
             << "\n";
    }
    cout << "========================================================\n\n";
}

void Menu::delete_food(){
    int id_delete;
    char cmd;
    show_menu();
    cout << "Slect id that you want to Delet!";
    cin >> id_delete;
    for(int i=0;i < id.size();i++){
        if(id_delete == id[i]){
            cout << "You want to delete: " << Name[i]  << " (ID " << id[i] << ")? (Y/N): ";
            cin >> cmd;
            if(cmd == 'Y'){
                id.erase(id.begin() + i);
                Name.erase(Name.begin() + i);
                category.erase(category.begin() + i);
                price.erase(price.begin() + i);
                cout << "Deleted successfully!\n";
                
            }

        }
    }
    // (ค่อยเติม logic ลบทีหลัง)
}

void Menu::update_food(){
    // (ค่อยเติม logic อัปเดตทีหลัง)
}

int main(){
    Menu m;
    int Command;

    while(true){
        m.showmessage();
        cout << "Input number : ";
        cin >> Command;

        if(Command == 1){
            m.get_food_name();
        }else if(Command == 2){
            m.delete_food();
        }else if(Command == 3){
            m.show_menu(); // ✅ เดิมเรียก show_menu ตอน 3 แต่เมนูเขียน UPDATE
        }else if(Command == 4){
            break;
        }else{
            cout << "invalid input\n";
        }
    }
}
