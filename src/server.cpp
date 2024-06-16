#include <iostream>
#include <boost/asio.hpp>
#include "../src/server.h"
#include<thread>
#include<memory>
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

    auto client_socket = make_shared< tcp::socket> (move(socket)); //creates a socket for the currect client


    {
        lock_guard <mutex> lock(this->clients_mutex);//locks the transaction
        clients.push_back(client_socket);//pushes the current client socket to the clients list

    }




    try{
        while(true){
            boost::system::error_code error;
            //reads from the socket buffer and inserts into data or gives errors if any
            size_t length = client_socket->read_some(boost::asio::buffer(this->data) , error);

            if(error == boost::asio::error::eof){
                break; 
            }
            else if(error){
                throw boost::system::system_error(error);
            }
            //write the data of length given back to the socket
           string message(this->data , length); //makes an object calles message of the string class 
           //it will assign the first (length) characters to the data array;

           broadCastMessageToClients(message , client_socket);
        }
    }
    catch(exception& err){
        cerr << "Exception in Thread " << err.what() << "\n";
    }


    lock_guard <mutex> lock(clients_mutex);

    clients.erase(remove(clients.begin() , clients.end() ,client_socket) , clients.end());
    //what the above code this is it will remove the current client socket from the list of the clients when it disconnects
    /*
        the remove function reorders the array or vector in such a way that the value that we give it will appear at the end
        of the array eg
        [1 , 2 , 3 , 4] is a vector called vec;
        then remove(vec.begin() , vec.end() , 3);will make the array appear like this
        [1 ,2 ,4 ,4] and return an iterator with the pointer to the last element in this case second 4

        erase method removes element from the vector
        its syntax is vec.erase(startrange , endrange );
        so in this case it will erase the element starting from the return value of the remove function which is the pointer to the
        second 4 to the end of the vector which is again the second 4 resulting in the removal of the value we wanted

        vec.erase(remove(vec.begin() , vec.end() , 3) , vec.end())
    */
}

void Server::broadCastMessageToClients(const string& message , shared_ptr<tcp::socket> sender){
 
    lock_guard <mutex> lock(clients_mutex); //locks the transaction(client_mutex)
 
    for(auto& client : this->clients){
        //a foreach loop which will iterate over all the clients and if the client is not the
        //sender of the message then it will send the message to all the connected clients 
 
        if(client != sender){
 
            boost::asio::write(*client , boost::asio::buffer(message));
 

        }
 
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