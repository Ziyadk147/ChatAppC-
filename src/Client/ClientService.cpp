#include<iostream>
#include<boost/asio.hpp>
#include "../Client/ClientInterface.h"

void Client::readFromServer(shared_ptr <tcp::socket> socket){
    try{
        while(true){

            boost::system::error_code error;

            size_t messageLength = socket->read_some(boost::asio::buffer(this->inComingData) , error);

            if(error == boost::asio::error::eof){
                cout << "User Disconnected \n";
                break;

            }
            else if(error){
                throw boost::system::error_code(error);
            }
            cout << "Reply From User: ";
            cout.write(this->inComingData , messageLength);
            cout << "\n";
        }
    }
    catch(exception& error){
        cerr << "Exception Occured: " << error.what() << "\n";
    }
}

void Client::writeToServer(shared_ptr <tcp::socket> socket){
    try{
        while(true){
            cout << ">> ";
            getline(cin , this->outGoingData);

            if(this->outGoingData == "exit" || this->outGoingData == "EXIT"){
                cout << "BYE!" << "\n";
                exit(200);
            }
            boost::asio::write(*socket , boost::asio::buffer(this->outGoingData));
        }
    }
    catch(exception& error){
        cerr << "Exception Occured: " << error.what() << "\n";
    }

};
void Client::getDataFromUser(){

    string  tempIP ;
    int tempPort;
    system("clear");
    cout << "Welcome Random User!! :) \n Please Enter the Server's Connection Details\nPlease Enter the Server ip or if the server is running on same machine type localhost\n";

    cin >> tempIP;

    if(tempIP == "localhost" || tempIP == "LOCALHOST"){

        this->serverIP = "127.0.0.1";
    }

    cout << "\nPlease Enter the port of the server\n";
    cin >> this->serverPort;

    system("clear"); 

}
string Client::getServerIPAddr(){
 
    return this->serverIP;

}
int Client::getServerPortAddr(){
    return this->serverPort;
}