#include<iostream>
#include<thread>

#include "client.h"
// #include "server.h"
using namespace std;

Client::Client(){
    // Client::Server(8080 , "127.0.0.1");
}
Client::Client(string ip, int port ){
    // Client::Server(port , ip);
}

void Client::readFromServer(shared_ptr<tcp::socket> socket){
    try{
        while (true)
        {
            boost::system::error_code error;
            size_t messageLength  = socket->read_some(boost::asio::buffer(this->receiveData) , error);

            if(error == boost::asio::error::eof){
                throw "User Left :( ";
            }
            else if (error){
                throw boost::system::error_code(error);
            }

            cout << "Reply: ";
            cout.write(this->receiveData , messageLength);
            cout << "\n";
        }
        
    }
    catch(exception& error){
        cerr << "Exception Caught: " << error.what() << "\n";
    }

}
void Client::writeToServer(shared_ptr<tcp::socket> socket){
    try{
        string msg;
        while(true){
            
            cout << ">>|";
            getline(cin ,msg);

            if(msg == "exit" || msg == "EXIT"){
                break;
            }

            boost::asio::write(*socket , boost::asio::buffer(msg));
        }
    }
    catch(exception& error){
        cerr << "Exception occured " << error.what() << "\n";
    }    
}

// int Client::getServerPort(){
//     return Client::Server::getPort();
// }

// string Client::getServerIP(){
//     return Client::Server::getIP();
// }

int main(){
    try{
        Client client("127.0.0.1" , 8080);
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context) ; //creating  a resolver object that will perform DNS lookcups

        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1" , "8080");
        //resovlves the ip and port to a list of enpoints

        auto socket = make_shared<tcp::socket>(io_context);
        // tcp::socket socket(io_context);
        boost::asio::connect(*socket , endpoints);
    
        thread readThread([&client](shared_ptr<tcp::socket> socket){client.readFromServer(socket);} , socket ); 
            /*
            created a thread which can be thought of as an extra worker or a processor which will
            read the data from the server and also write to it asynchrounusly 
            the above threads takes two arguments one is the function which is to be processed and 2nd is
            its argument
            readThread(readfromserver , socket)
            but since readFromServer is a member of the Client class we have to user a lambda function 
            lambda functions are unnamed functions syntax is
            [capture](arguments if any){work to do}
            capture can be anything that can be used in the function
            here we have passed the client object by reference which takes a tcp::socket as input and then calls
            the readFromServer function of the client class and moves the tcp::socket in it
            */


        client.writeToServer(socket);
        socket->close();
        readThread.join();
    }
    catch(exception& error){
        cerr << "Exception Occured " << error.what() << "\n";
    }

};