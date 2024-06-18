#ifndef ORM_H
#define ORM_H


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
    protected:
        Driver *driver;
        Connection *connection;
        Statement *statement;
        ResultSet *resultset;
        void createDatabaseIfNotExists(string database);
        
        bool checkIfDatabaseExists(string dbName);
        bool checkIfTableExists(string tableName);
    


    public:
        ORM();
        vector<string> getPropertiesFromUser();
        Connection* createConnection( vector<string> connectionProperties); 
          // ResultSet* raw(string query);
        // void createRecord();


};
#endif