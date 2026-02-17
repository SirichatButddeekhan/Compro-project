#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
struct User{
   string username;
   string password;
};
void add_user(vector<User>& user);
   
bool check_login(const vector<User>& user, const string& input_user, const string& input_pass);
    
void saveuser(const string& u, const string& p);
void loaduser(vector<User>& user );
int main(){
    //ประกาศตัวแปรเก็บข้อมูลผู้ใช้

   vector<User> user;
   loaduser(user);
    //เพิ่มผู้ใช้ใหม่ถ้าไม่มี
    string answer;
    cout<<"you have username ? (yes or no) "<<endl;
    cin>>answer;

    if (answer=="no"){
        add_user(user);

    } 
    //เข้าสู่ระบบ
    while(true){
        cout<<"login page"<<endl;
        bool key=false;
        string input_user;
        cout<<"Enter username: ";
        cin>>input_user;
        string input_pass;
        cout<<"Enter password: ";
        cin>>input_pass;
        key=check_login(user, input_user, input_pass);//ตรวจสอบการเข้าสู่ระบบ
    if (key){
        cout<<"Login successful!"<<endl;
        break;
    }else{
        cout<<"Login failed. Please try again."<<endl;
    }

      }  
   
    }
    void add_user(vector<User>& user){ //เพิ่มผู้ใช้ใหม่
    User new_user;
    cout<<"Enter new username: ";
    cin>>new_user.username;
    cout<<"Enter new password: ";
    cin>>new_user.password;
    user.push_back(new_user);
    saveuser(new_user.username, new_user.password);
}
bool check_login(const vector<User>& user, const string& input_user, const string& input_pass){ //ตรวจสอบการเข้าสู่ระบบ
    for (const User& u : user){
        if (u.username == input_user and u.password == input_pass){
            return true;
        }
    }
    return false;
}
void saveuser(const string& u, const string& p){ //บันทึกข้อมูลผู้ใช้ลงไฟล์
    ofstream file("userandpass.txt", ios::app);
    file << u << " " << p << endl;
    file.close();
}
void loaduser(vector<User>& user){ //โหลดข้อมูลผู้ใช้จากไฟล์
    ifstream file("userandpass.txt");
    User u;
    while (file >> u.username >> u.password){
        user.push_back(u);
    }
    file.close();
}