#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "ORM.h"
#include <vector>

using namespace std;
using namespace sql;


ORM::ORM(){

    this->driver = get_driver_instance();
    // this->connectionProperties = ORM::getPropertiesFromUser();
};

//pointer Connection* because  Connection throws error

vector<string> ORM::getPropertiesFromUser(){
    vector <string> tempVector;
    string tempInput;
    
    cout << "Enter your Connection string" << endl;
    cin >> tempInput;

    tempVector.push_back(tempInput);

    cout << "Enter your Database Username" << endl;
    cin >> tempInput;

    tempVector.push_back(tempInput);

    cout << "Enter your Database Password " << endl;
    cin >> tempInput;

    tempVector.push_back(tempInput);
    
    
    cout << "Enter your Database name " << endl;
    cin >> tempInput;

    tempVector.push_back(tempInput);
    
    
    return tempVector;
    
}


Connection* ORM::createConnection(vector<string> connectionProperties){
    
    try{
        string connectionAddr = connectionProperties[0];
        string username = connectionProperties[1];
        string password = connectionProperties[2];
        string database = connectionProperties[3];


        this->connection = driver->connect(connectionAddr , username , password );
        this->connection->setSchema(database);

        if(this->connection){

            cout << "Connected";
            return this->connection;
        }
    }
    catch(SQLException &e){
        cout << "SQL EXCEPTION " << e.what() << endl;
        cout << "SQLState" << e.getSQLState() << endl;
    }
    return 0;
};

