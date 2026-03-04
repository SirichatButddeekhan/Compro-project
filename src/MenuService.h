#pragma once
#include <vector>
#include <string>

struct MenuItem {          // ✅ ต้องอยู่นอก class Menu
    int id{};
    double price{};
    std::string name;
};

class Menu {
public:
    std::vector<MenuItem> m;

    void LoadCSV(const std::string& filename);
    void SaveCSV(const std::string& filename); 
    void CREATE(const MenuItem& item);
    void Read();
    void Delete(int id);
    void Update(int id, const MenuItem& newItem);
};