#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <vector>

#include "../Server/ServerInterface.h"



using namespace std;
using namespace boost::asio::ip;


void Server::createConnection(tcp::socket socket){
    //creating a socket for the current client
    auto client_socket = make_shared<tcp::socket> (move(socket));

    {
        lock_guard <mutex> lock(this->client_mutex); //locks the transaction
        clients.push_back(client_socket);//pushes the current client socket to the clients list 

    }

    try{
        while(true){
            boost::system::error_code error;
            //reads data from the socket and assigns the length to the lengeth and assign error to error if any
            size_t length = client_socket->read_some(boost::asio::buffer(this->data) , error);

            if(error == boost::asio::error::eof){
                // cout << "Client Disconnected" << "\n";
                break;                
            }
            else if(error){
                throw boost::system::error_code(error);
            }

            //makes a message object of string class with tha data in this->data and reads till the given length
            string message(this->data , length);

            this->broadCastMessageToClients(message , client_socket);
        }
        



    }
    catch(exception& e){
        cerr << "Exception Occured " << e.what() << "\n"; 
    }

    lock_guard <mutex> lock(this->client_mutex);
    clients.erase(remove(clients.begin() , clients.end() , client_socket) , clients.end());
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
void Server::broadCastMessageToClients(string& message , shared_ptr<tcp::socket> sender){
    for(auto& client:clients){
        
        if(client != sender){
            
            boost::asio::write(*client , boost::asio::buffer(message));

        }

    }  
}
void Server::getDataFromUser(){

    cout << "Welcome to the chat Server\nEnter the port you want to run the server on\n";

    cin >> this->port;

}
Server::Server(){

    this->getDataFromUser();
    this->ip = "127.0.0.1";

}

