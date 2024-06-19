#include "../Models/User.h"


void User::getUserNameFromDB(string userName){

    ResultSet* SQLresult =  where("username" , "users" , "username" , "=" , userName);
    // where("SELECT * FROM users");
    while(SQLresult->next()){
        
        this->username =  SQLresult->getString(1);
    

    }
}

int main(){
    User user;
    user.getUserNameFromDB("ziyad");
}



