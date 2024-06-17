#include<iostream>
#include<boost/asio.hpp>
#include "../Server/ServerService.cpp"

using namespace std;
using namespace boost::asio::ip;


int main(){
    try{
        Server server;  
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context , tcp::endpoint(tcp::v4() , server.port));
    
        while(true){
            tcp::socket socket(io_context);
            
            acceptor.accept(socket);

            thread(
                [&server](tcp::socket socket){
                    server.createConnection(move(socket));
            } , move(socket)).detach();

            /*
                creates a thread which takes address of server class to be used in a lambda function and then moves the socket
                into the createConnection function 
            */

        }
    
    }
    catch(exception& err){
        cerr << "Exception Occured " << err.what() << "\n";
    }
}