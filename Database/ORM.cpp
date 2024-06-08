#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "ORM.h"

using namespace std;
using namespace sql;


ORM::ORM(){
    this->driver = get_driver_instance();
};

//pointer Connection* because  Connection throws error

void ORM::createConnection(string *properties){
    
    try{
        this->connectionAddr = properties[0];
        this->userName = properties[1];
        this->password = properties[2];
        this->database = properties[3];


        this->connection = driver->connect(this->connectionAddr , this->userName , this->password );
        this->connection->setSchema(this->database);

        if(this->connection){

            cout << "Connected";
        
        }
    }
    catch(SQLException &e){
        cout << "SQL EXCEPTION " << e.what() << endl;
        cout << "SQLState" << e.getSQLState() << endl;
    }
    
};