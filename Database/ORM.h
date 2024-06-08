#include<iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql;

class ORM {
    private:
        Driver *driver;
        Connection *connection;
        Statement *statement;
        ResultSet *resulset;


        string connectionAddr;
        string userName;      
        string password;
        string database;



    public:
        ORM();
        void createConnection(string *properties);
        


};
