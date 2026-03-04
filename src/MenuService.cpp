#include "MenuService.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

void Menu::LoadCSV(const std::string& filename) {
    std::ifstream file(filename);
    m.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id_str, name, price_str;

        std::getline(ss, id_str, ',');
        std::getline(ss, name, ',');
        std::getline(ss, price_str, ',');

        if (id_str.empty() || name.empty() || price_str.empty()) continue;

        MenuItem item;
        item.id = std::stoi(id_str);
        item.name = name;
        item.price = std::stod(price_str);
        m.push_back(item);
    }
}

void Menu::SaveCSV(const std::string& filename) {

    std::ofstream file(filename);

    for (const auto& item : m) {
        file << item.id << "," 
             << item.name << "," 
             << item.price << "\n";
    }

}

void Menu::CREATE(const MenuItem& item) {
    m.push_back(item);
}

void Menu::Read() {
    for (const auto& item : m) {
        std::cout << item.id << " | " << item.price << " | " << item.name << "\n";
    }
}

void Menu::Delete(int id) {
    m.erase(
        std::remove_if(m.begin(), m.end(),
            [id](const MenuItem& item) { return item.id == id; }),
        m.end()
    );
}

void Menu::Update(int id, const MenuItem& newItem) {
    for (auto& item : m) {
        if (item.id == id) {
            item.price = newItem.price;
            item.name  = newItem.name;
            return;
        }
    }
}   