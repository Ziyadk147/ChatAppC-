#ifndef USER_H
#define USER_H

#include <iostream>
#include "../ORM.h"


class User : public ORM{
    private:
    
        string username;
        string password;
    
    public:
    
        void getUserNameFromDB(string userName);
        void getPassWordFromDB(string userName);    
        
};

#endif