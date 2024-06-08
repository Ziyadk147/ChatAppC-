#include<iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <vector>

using namespace std;
using namespace sql;

class ORM {
    private:
        Driver *driver;
        Connection *connection;
        Statement *statement;
        ResultSet *resultset;

    
    protected:
        vector<string> connectionProperties;
        vector<string> getPropertiesFromUser();


    public:
        ORM();
        void createConnection();
        // ResultSet* raw(string query);
        // void createRecord();


};
