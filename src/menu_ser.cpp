#include "menu.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <codecvt>
#include <locale>

std::wstring StringToWString(const std::string& str)
{
    return std::wstring(str.begin(), str.end());
}

void Menu::LoadCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return;

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
        item.name = StringToWString(name);
        item.price = std::stod(price_str);

        m.push_back(item);
    }
}

bool Menu::SaveCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& item : m) {
        std::string name(item.name.begin(), item.name.end());

        file << item.id << "," << name << "," << item.price << "\n";
    }

    return true;
}

bool Menu::CheckId(int id) const {
    for (const auto& item : m) {
        if (item.id == id) return true;
    }
    return false;
}

void Menu::CREATE(const MenuItem& item) {
    m.push_back(item);
}

void Menu::Update(int id, const MenuItem& newItem) {
    for (int i = 0; i < (int)m.size(); i++) {
        if (m[i].id == id) {
            m[i].name  = newItem.name;
            m[i].price = newItem.price;
            return;
        }
    }
}

void Menu::Delete(int id) {
    m.erase(
        std::remove_if(m.begin(), m.end(),
            [id](const MenuItem& item) { return item.id == id; }),
        m.end()
    );
}