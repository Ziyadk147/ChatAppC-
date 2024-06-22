#ifndef USER_H
#define USER_H

#include <iostream>
#include "../ORM.h"


class User : public ORM{
    private:
    
        string username = "";
        string password = ""; 
    
    public:
    
        string getUserNameFromDB(string userName);
        string getPassWordFromDB(string userName);    
        void   insertUserToDB(string username , string password);
                
        string getUserName();
        string getUserPassword();
        void userLoginInput();
        bool checkIfUserExists(string username);

};

#endif