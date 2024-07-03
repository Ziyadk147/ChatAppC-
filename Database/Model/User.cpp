#include "../Model/User.h"


// string User::getUserNameFromDB(string username){
//     ResultSet *userresult;

//     string query = "SELECT username  FROM users WHERE username = \""+username+"\" LIMIT 1";
    
//     userresult = raw(query);

//     string user =  parseSingleString(userresult);

//     delete userresult;
//     return user;
// };

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

        // cout << foundName << endl << ername;
    // cout << endl << username << endl << foundName;
    
        return true;

    }

    else{
    // cout << endl << username << endl << foundName;
        
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

// int main(){
//     User user;
//     user.insertUserinDB("testuser2" , "12345");
//     if(user.authenticateUser("testuser" , "12345")){
        
//         cout << "\n Welcome testuser1\n";
    
//     }

//     else{
//         cout << "\n dafa ho bkl";
//     }
   