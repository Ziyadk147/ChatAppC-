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
void Client::startClient(Client client){
           // if(client.authenticateUser()){
        try{
            boost::asio::io_context io_context;
            tcp::resolver resolver(io_context); //creating  a resolver object that will perform DNS lookcups

            client.getDataFromUser();
            
            tcp::resolver::results_type endpoints = resolver.resolve(client.getServerIPAddr() , to_string(client.getServerPortAddr()));
            //resovlves the ip and port to a list of enpoints

            auto socket = make_shared <tcp::socket>(io_context);

            boost::asio::connect(*socket , endpoints);

            thread read_thread(
                [&client](shared_ptr <tcp::socket> socket){
                
                    client.readFromServer(socket);
                
                } , socket );
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
            read_thread.join();
        }
        
        catch(exception& error){
            cerr << "Exception Occured " << error.what() << "\n";
        }
        // }
        // else{
        //     client.registerUser();

        // }
            
    }


string Client::getServerIPAddr(){
 
    return this->serverIP;

}
int Client::getServerPortAddr(){
    return this->serverPort;
}