#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<limits>
using namespace std;
struct User{ //โครงสร้างข้อมูลผู้ใช้
   string username;
   string password;
};
//ฟังก์ชันประกอบการทำงานของระบบ
void add_user(vector<User>& user);
   
bool check_login(const vector<User>& user, const string& input_user, const string& input_pass);
    
void saveuser(const string& u, const string& p);
void loaduser(vector<User>& user );
bool check_user(const vector<User>& user, const string& inputnew_user);
bool nohas_space(const string& str);
int main(){
    //ประกาศตัวแปรเก็บข้อมูลผู้ใช้

   vector<User> user;
   loaduser(user);
    //เพิ่มผู้ใช้ใหม่ถ้าไม่มี
    string answer;
    while(true){    //เช็คว่ามีผู้ใช้หรือไม่ ถ้าไม่มีให้เพิ่มผู้ใช้ใหม่ ถ้ามีแล้วให้เข้าสู่ระบบ พิมพ์มั่ววนใหม่
        cout<<"you have username ? (yes or no) "<<endl;
        cin>>answer;
        if (answer=="no"){
            add_user(user);
            break;
        } else if (answer=="yes"){
            break;
        } else{
            cout<<"Invalid input. Please enter 'yes' or 'no'."<<endl;
        }
    }

   
    //เข้าสู่ระบบ
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ล้าง\n
    while(true){ //วนลูปจนกว่าจะเข้าสู่ระบบสำเร็จ
        cout<<"login page"<<endl;
        bool key=false;
        string input_user;
        cout<<"Enter username: ";
        getline(cin, input_user);
        string input_pass;
        cout<<"Enter password: ";
        getline(cin, input_pass);
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ล้าง\n
    cout<<"Enter new username: ";
    getline(cin, new_user.username);
 while(check_user(user, new_user.username)==false || nohas_space(new_user.username)==false){//ตรวจสอบว่าชื่อผู้ใช้ซ้ำหรือมีช่องว่างหรือไม่ ถ้ามีให้พิมพ์ใหม่
            if (nohas_space(new_user.username)==false){
                cout<<"Username has space. Please enter a  username again: ";
            } else {
                cout<<"Username dupplicate. Please enter a different username: ";
            }
            getline(cin, new_user.username);
        }
    cout<<"Enter new password: ";
    getline(cin, new_user.password);
    while(nohas_space(new_user.password)==false){
        cout<<"Password has space. Please enter a password again: ";//ตรวจสอบว่ารหัสผ่านมีช่องว่างหรือไม่ ถ้ามีให้พิมพ์ใหม่
        getline(cin, new_user.password);
    }
    user.push_back(new_user);
    saveuser(new_user.username, new_user.password);
}
bool check_login(const vector<User>& user, const string& input_user, const string& input_pass){ //ตรวจสอบการเข้าสู่ระบบ
    for (const User& u : user){//วนลูปตรวจสอบว่าชื่อผู้ใช้และรหัสผ่านตรงกับข้อมูลที่มีอยู่หรือไม่ ถ้าตรงให้ return true ถ้าไม่ตรงให้ return false
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
    while (file >> u.username >> u.password){//อ่านข้อมูลจากไฟล์และเก็บไว้ในตัวแปร u [ {ming555,1230}, {admin,9999} ]

        user.push_back(u);
    }
    file.close();
}
bool check_user(const vector<User>& user, const string& inputnew_user){ //ตรวจสอบว่ามีผู้ใช้นี้อยู่แล้วหรือไม่
    for (const User& u : user){
        if (u.username == inputnew_user){
            return false;
        }
    }
    return true;
}
bool nohas_space(const string& str){ //ตรวจสอบว่ามีช่องว่างในชื่อผู้ใช้หรือไม่
    for (char c : str){//char c รับค่าที่ละตัวใน str เเละวนลูปจนกว่าจะครบทุกตัว ถ้ามีช่องว่างจะ return false
        if (c == ' '){
            return false;
        }
    }
    return true;
}