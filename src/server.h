#ifndef SERVER_H
#define SERVER_H


#include<iostream>
#include<boost/asio.hpp>
#include<mutex>
#include<vector>
#include<memory>
using namespace std;
using namespace boost::asio::ip;

class Server {
    private:
        char data[256];
        std::vector<shared_ptr<boost::asio::ip::tcp::socket>> clients; //list of clients with shared pointer of type tcp::socket to handle memory
        std::mutex clients_mutex; //creates a client_mutex which can be thought of transactions in DB

        void broadCastMessageToClients(const string& message , std::shared_ptr <boost::asio::ip::tcp::socket> sender);

    public:
        string ip_addr;
        int port;

        Server();
        Server(int connPort , string ipAddr);

        void createServerSession(tcp::socket socket);

        tcp::socket createSocket(boost::asio::io_context iocontext);
        string getIP();
        int getPort();
};

#endif