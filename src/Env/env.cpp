#include <iostream>
#include <fstream>
#include <map>
#include "env.h"


string Environment::trim(const string& message){
    size_t first = message.find_first_not_of(" ");
    size_t last = message.find_last_not_of(" ");


    return message.substr(first , (last - first + 1));
};


map <string , string> Environment::env(string& filename){
    map <string , string> config ; //declares an associative array or a dict to store key value pairs; 

    ifstream file(filename);

    if(!file.is_open()){
        cerr << "\nUnable to open env file\n";
        return config;
    }

    string line;
    while(getline(file , line)){
        size_t position = line.find("=");

        if(position != string::npos){
            string key = trim(line.substr(0 , position));
            string value = trim(line.substr(position + 1));

            config[key] = value;
        }
    }
    file.close();
    this->envDict = config ;
    return config;
}


string Environment::getConnectionString(){

    
    return this->envDict["DATABASE_HOST"];

}

string Environment::getDBUsername(){
    
    return this->envDict["DATABASE_USERNAME"];

}
string Environment::getDBPassword(){
    
    return this->envDict["DATABASE_PASSWORD"];

}

string Environment::getDBName(){

    return this->envDict["DATABASE_NAME"];

}

// int main(){
//     Environment environ;

//     cout << environ.getConnectionString() << endl << environ.getDBName() << endl << environ.getDBPassword() << endl << environ.getDBUsername();

// }