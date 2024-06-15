#include <iostream>
#include <boost/asio.hpp>
#include "../src/server.h"
using namespace std;
using namespace boost::asio::ip;

Server::Server(){
    this->port = 8080;
    this->ip_addr = "127.0.0.1";
}
Server::Server(int connPort , string ipAddr){
    this->port = connPort;
    this->ip_addr = ipAddr;
}
void Server::createServerSession(tcp::socket socket){
    try{
        while(true){
            boost::system::error_code error;
            //reads from the socket buffer and inserts into data or gives errors if any
            size_t length = socket.read_some(boost::asio::buffer(this->data) , error);

            if(error == boost::asio::error::eof){
                break; 
            }
            else if(error){
                throw boost::system::system_error(error);
            }
            //write the data of length given back to the socket
            boost::asio::write(socket , boost::asio::buffer(this->data ,length));
        }
    }
    catch(exception& err){
        cerr << "Exception in Thread " << err.what() << "\n";
    }
}

int main(){
    try {
        Server server;
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context , tcp::endpoint(tcp::v4() , server.port));
        while(true){
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            thread([&server](tcp::socket socket){server.createServerSession(move(socket));},move(socket)).detach(); 
            //learn about the above line

        }
    }
    catch(exception& error){
        cerr << "Exception: " << error.what() << "\n";
    }
}