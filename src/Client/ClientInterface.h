#ifndef CLIENT_INTERFACE_H
#define CLIENT_INTERFACE_H

#include <iostream>
#include <boost/asio.hpp>
#include "../Server/ServerInterface.h"
#include "User.h"

using namespace std;
using namespace boost::asio::ip;

class Client : public User {
    private:
        string outGoingData;
        string serverIP;
        char inComingData[256];

        int serverPort;

  
    public:
        
        void readFromServer(shared_ptr<tcp::socket> socket);
        void writeToServer(shared_ptr <tcp::socket> socket);
        void getDataFromUser();
        string getServerIPAddr();
        int getServerPortAddr();        

        bool registerOrLogin();
        void registerUser();
        void loginUser();
        // void getServerIP();


};



#endif