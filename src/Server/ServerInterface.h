#ifndef SERVER_INTERFACE_H
#define SERVER_INTERFACE_H

#include<iostream>
#include<mutex>
#include<vector> 
#include<boost/asio.hpp>
 
using namespace std;
using namespace boost::asio::ip;

class Server {
    private:
        mutex client_mutex;
        vector <shared_ptr <tcp::socket>> clients; //creates a vector of shared pointer of type tcp socket of all the clinets;
    
        char data[256];

        void broadCastMessageToClients(string& message , shared_ptr <tcp::socket> sender);
        void getDataFromUser();
    
    public:
        string ip;
        int port;


        Server();
        // Server(string ip , int port);

        void createConnection(tcp::socket  socket);

        // tcp::socket createSocket(boost::asio::io_context io_context);

        int getServerPort();
        string getServerIP();

};
#endif