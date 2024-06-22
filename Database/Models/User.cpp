#include "../Models/User.h"



void User::userLoginInput(){
         
            string tempname;
            string temppass;
            char tempChoice;
            
            cout << "\nWelcome To The Chat Application\nPlease Enter your  Username to Proceed\n";
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

void User::insertUserToDB(string username , string password){
    string values =  "\""+username+"\""+ " , " + "\""+password+"\"";

    ResultSet *SQLresult = insert("users","username , password ", values );

    // cout << parseSingleString(SQLresult);
    delete SQLresult;
}

bool User::checkIfUserExists(string username){
    
    if(!this->getUserNameFromDB(username).empty()){
        return true;
    }
    else{
        return false;
        
    }

}
string User::getUserName(){
    
    return this->username;

}

string User::getUserPassword(){
    
    return this->password;

}
