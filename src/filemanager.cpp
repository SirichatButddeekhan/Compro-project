#include "filemanager.h"
#include <fstream>
#include <string>
bool checkLogin(string user,string pass){
    ifstream file("userandpass.txt");
    bool found =false;
    string userline,passline;
    while(file>> userline >> passline) {
        if (user == userline && pass == passline) {
            found = true;
            break;
        }
    }
    file.close();
    return found;
}