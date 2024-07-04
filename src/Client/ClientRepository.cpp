#include "../Client/ClientInterface.h"

bool Client::registerOrLogin(){
    
    system("clear");
    
    int choice;

    cout << "Welcome User!\nSelect!\n1)Register\nany key for login\n";

    cin >> choice;

    if (choice == 1){
    
        return true;
    
    }
    else{
        
        return false;
    
    }

}
void Client::registerUser(){
    bool choice = true;
    do{
        system("clear");
        string username , password;
        
        cout << "Register\nPlease enter your username\n";
        
        cin >> username;

        if(checkIfUserExistsInDB(username)){
            
            char temp;
            cout << "\nUser Already Exists\npress any key to continue...\n";
            cin >> temp;
            continue;

        }    
        else{

            cout << "\nPlease enter your desired password\n";
            cin >> password;
            insertUserinDB(username , password);
            cout << "\nWelcome " << username << "\n";
            choice = false;

        }
    }
    while(choice == true);
    
}

void Client::loginUser(){
    system("clear");
    
    string username , password;
    bool choice = true;

    do{
        system("clear");
        char temp;
    
        cout<<"Login\nPlease Enter Your Registered Username\n";
        cin >> username;

        cout << "\nPlease Enter Your Password\n";
        cin >> password;
        
        system("clear");

        if(authenticateUser(username , password)){
            cout << "Welcome " << username << "\nPress any key to continue..\n";
            cin >> temp;
            choice = false;
        }
        else{
            cout << "\nIncorrect Username Or Password\npress any to continue\n";
            cin >> temp;    
            continue;
        }
    }
    while(choice == true);
    
}
    