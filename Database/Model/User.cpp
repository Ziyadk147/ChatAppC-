#include "../Model/User.h"


string User::getPasswordFromDB(string username){

    ResultSet *userresult;
    
    string query = "SELECT password FROM users WHERE username = \""+username+"\" LIMIT 1";  

    userresult = raw(query );

    string password = parseSingleString(userresult);

    return password;

}


bool User::checkIfUserExistsInDB(string username){

    ResultSet *userresult;

    int noOfRecords = 0;

    string query = "SELECT username  FROM users WHERE username = \""+username+"\" LIMIT 1";
    
    userresult = raw(query);

    string foundName = parseSingleString(userresult);
    
    delete userresult;
    
    if(foundName == username && !foundName.empty()){
    
        return true;

    }

    else{

        
        return false;

    }
}

void  User::insertUserinDB(string username , string password){
    
    string tablename = "users";

    string columns = "username , password" ;
    
    string values = "\""+username+"\",\""+password+"\"";

    insert(tablename , columns , values);

}

bool User::authenticateUser(string username , string password){

    if(checkIfUserExistsInDB(username)){
        
        string dbUsername = username;
        string dbPassword =  getPasswordFromDB(dbUsername);

        if(dbPassword == password){
            
            setUserName(dbUsername);
            setPassword(dbPassword);

            return true;
        
        }
        else{
            
            return false;
        
        }
    }
    
    else{
    
        return false;
    
    }
}


int User::getUserID(string username){

    string name;

    if(username.empty()){
    
        name = this->username;
    
    }
    else{
    
        name = username;
    
    }
    string query = "SELECT id FROM users WHERE username = \""+name+"\" LIMIT 1;";

    ResultSet *result = raw(query);

    int id = parseSingleInt(result);

    return id;      
}

void User::setUserName(string name){

    this->username = name;

}

void User::setPassword(string password){
    
    this->password = password;

}

string User::getUserName(){
 
    return this->username;

}
