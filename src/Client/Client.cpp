#include <iostream>
#include <thread>
// #include <boost/asio.hpp>
#include "../Client/ClientService.cpp"
#include "../Client/ClientInterface.h"
#include "../Client/ClientRepository.cpp"

using namespace std;
// using namespace boost::asio::ip;

const int LOGIN = 1;
const int REGISTER = 2;
const int EXIT = 3;

int main(){

        Client client;
        if(client.registerOrLogin() == LOGIN){
            if(client.authenticateUser()){
                client.startClient(client);
            }
            else{
                cout << "\n Exiting\n";
                system("exit");
            };

        }
        else if(client.registerOrLogin() == REGISTER){
            // if(client.registerUser()){
                
            //     client.startClient(client);
            
            // }
            // else {
            
            //     cout << "\ns\n";
            //     // system("exit");
            
            // }
            cout << client.registerUser();

        }
        else{
                cout << "\n Exiting\n";
                system("exit");
        }
    }
 
