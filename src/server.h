#include<iostream>
#include<boost/asio.hpp>

using namespace std;
using namespace boost::asio::ip;

class Server {
    private:
        char data[256];
    public:
        string ip_addr;
        int port;

        Server();
        Server(int connPort , string ipAddr);

        void createServerSession(tcp::socket socket);

        tcp::socket createSocket(boost::asio::io_context iocontext);
};
