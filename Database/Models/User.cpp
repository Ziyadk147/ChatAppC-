#include "../Models/User.h"



void User::userLoginInput(){
        
            string tempname;
            string temppass;
            char tempChoice;
            
            cout << "\nWelcome To The Chat Application\nPlease Enter your registered Username to Proceed\n";
            cin  >> tempname;

            this->username = tempname;

            cout << "\nPlease Enter your password\n";
            cin >> temppass;
          
            this->password = temppass;
};

string User::getUserNameFromDB(string userName){

    ResultSet* SQLresult =  where("username" , "users" , "username" , "=" , userName);
    // where("SELECT * FROM users");
    
    string tempname = parseSingleString(SQLresult);
    
    // cout << this->username;
    delete SQLresult;
    return tempname;

}

string User::getPassWordFromDB(string userName){
    
    ResultSet* SQLresult = where("password" , "users" , "username" , "=" , userName );
    
    string temppass = parseSingleString(SQLresult);
    

    delete SQLresult;
    
    return temppass;

    // cout << this->password;
}

string User::getUserName(){
    
    return this->username;

}

string User::getUserPassword(){
    
    return this->password;

}
// strin

// int main(){
//     User user;
//     user.getUserNameFromDB("ziyad");
//     user.getPassWordFromDB("ziyad");
// }



