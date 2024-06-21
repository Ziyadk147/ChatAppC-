// #include "../Database/Models/User.h"
#include "../Client/ClientInterface.h"

using namespace std;

bool Client::authenticateUser(){

    if(getUserName().empty() || getUserPassword().empty()){
    
        userLoginInput();
    
    }    

    string checkName =  getUserName();
    string checkPass = getUserPassword();

    string dbUserName = getUserNameFromDB(this->getUserName());
    if(!dbUserName.empty()){
        
        string dbPassword = getPassWordFromDB(dbUserName);

        if(checkName == dbUserName && checkPass == dbPassword){
            system("clear");
            // cout << "\ncorrect\n";
            return true;
        }else{
            system("clear");
            // cout << "\nIncorrect\n";
            return false;
        }

    }
    else{
        return false;
    }


    // if(!dbUserName.empty() && getPassWordFromDB(dbUserName) != this->getUserPassword()){
    
    //     cout << "\nInvalid username or Password\n";
    //     return false;
    
    // }
    // else{

    //     system("clear");

    //     cout << dbUserName;
    //     return true;
        
    // }
}

