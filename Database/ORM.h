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
        vector <string> connectionProps;
        void createDatabaseIfNotExists(string database); 
        bool checkIfDatabaseExists(string dbName);
        bool checkIfTableExists(string tableName);
    



    public:
        ORM();
        bool presetOrCustomConnectionProperties();
        vector<string> getPropertiesFromUser();
        Connection* createConnection( vector<string> connectionProperties); 
        ResultSet* rawQuery(string query);
        ResultSet* where(string columns , string tablename , string operand1 , string sqlOperator , string operand2);
        string parseSingleString(ResultSet* result);
          // ResultSet* raw(string query);
        // void createRecord();


};
#endif