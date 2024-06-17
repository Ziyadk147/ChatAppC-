#ifndef CLIENT_H
#define CLIENT_H


#include<iostream>

#include<boost/asio.hpp>
#include "server.h"


using namespace std;
using namespace boost::asio::ip;


class Client{
    private:
        string sendData;
        char receiveData[256];

    public:
        Client();
        Client(string ipAddr , int port);


        int getServerPort();
        string getServerIP();
        int connectionPort; 
        string connectionIP;


        void readFromServer(shared_ptr <tcp::socket> socket);
        void writeToServer(shared_ptr<tcp::socket> socket);
        void getConnectionDetailsFromUser();
};

#endif
