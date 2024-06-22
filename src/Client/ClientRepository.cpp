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
}
bool Client::registerUser(){
    userLoginInput();
    
    insertUserToDB(getUserName() , getUserPassword());
    return true;
    
    // if(checkIfUserExists(getUserName())){
        
    //     return false;
    
    // }
    // else{
        
    // }

}


int Client::registerOrLogin(){
    system("clear");
    int choice;
    
    cout << "Welcome to Chatapplication\nSelect the following options. Press any other key to exit the program\n1)Login\n2)Register\n";
    cin >> choice;
    
    if(choice == 1){
    
        return 1;
    
    }   
    else if(choice == 2){
    
        return 2;
    
    }
    else{

        return 3;
    
    }
    
} 