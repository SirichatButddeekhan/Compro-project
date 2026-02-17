#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct MenuItem {
    int id;
    string name;
    double price;
    bool available;
    string description;
};

class Restaurant {
private:
    vector<MenuItem> menu;

public:
    void loadMenu() {
        menu = {
            {1, "Fried Rice", 50, true, "a"},
            {2, "Pad Thai", 60, true, "b"},
            {3, "Tom Yum", 80, true, "c"},
            {4, "Somtum", 40, true, "d"},
           
        };
    }

    void showMenu() {
        cout << "\n=========== MENU ===========\n";

        for (auto &m : menu) {
            cout << "[" << m.id << "] "
                 << left << setw(15) << m.name
                 << " | " << m.price << " Baht\n";
        }

        cout << "============================\n";
    }
};

int main() {

    Restaurant app;
    app.loadMenu();

    int choice;

    while (true) {
        cout << "\n1. Show Menu\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            app.showMenu();
        }
        else if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
