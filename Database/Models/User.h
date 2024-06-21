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
        
        string getUserName();
        string getUserPassword();
        void userLoginInput();

};

#endif