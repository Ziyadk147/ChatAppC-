#include<iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include<vector>
#include "Database/ORM.h"

class Message : public ORM{
    private:
        vector<string> columns;
    public:
        Message(){
            
        }


};