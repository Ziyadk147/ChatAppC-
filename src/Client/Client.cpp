#include <iostream>
#include <thread>
// #include <boost/asio.hpp>
#include "../Client/ClientService.cpp"
#include "../Client/ClientRepository.cpp"

using namespace std;
// using namespace boost::asio::ip;


int main(){
    try{
        Client client;
        if(client.registerOrLogin()){
        
            client.registerUser();
        
        }    
        client.loginUser();
        
        


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

}