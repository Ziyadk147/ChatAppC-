#include "../Models/User.h"


void User::getUserNameFromDB(string userName){

    ResultSet* SQLresult =  where("username" , "users" , "username" , "=" , userName);
    // where("SELECT * FROM users");
    
    this->username = parseSingleString(SQLresult);
    
    cout << this->username;
    delete SQLresult;

}

void User::getPassWordFromDB(string userName){
    
    ResultSet* SQLresult = where("password" , "users" , "username" , "=" , userName );
    
    this->password = parseSingleString(SQLresult);
    
    delete SQLresult;
    cout << this->password;
}


int main(){
    User user;
    user.getUserNameFromDB("ziyad");
    user.getPassWordFromDB("ziyad");
}



