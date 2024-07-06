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



const int CONNECTION_STRING = 0;
const int USERNAME = 1;
const int PASSWORD = 2;
const int DBNAME  = 3;



ORM::ORM(){

    this->driver = get_driver_instance();
    // this->connectionProperties = ORM::getPropertiesFromUser();
};

//pointer Connection* because  Connection throws error

bool ORM::presetOrCustomSettings(){
    system("clear");
    int choice;
    
    cout << "\n Do you want to use the preset settings or do you want to input custom settings\n1)Preset\nany other key for custom settings\n";
    cin >> choice;

    if(choice == 1){
        return true;
    }
    else {
        return false;
    }
    

};

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

void ORM::createDatabaseIfNotExists(string database){
    
    try{
    
        string dbName = database;

        Statement* state = this->connection->createStatement();

        string query = "CREATE DATABASE IF NOT EXISTS " + dbName;

        state->execute(query);

        

        delete state;
    }
    catch(SQLException &e){

        cout << "SQL EXCEPTION " << e.what() << endl;
        cout << "SQLState" << e.getSQLState() << endl;

    }
};

bool ORM::checkIfTableExists(string tableName){
    try{
        Statement* state = this->connection->createStatement();
        string query =  "SHOW TABLES";

        ResultSet* table = state->executeQuery(query);

        while(table->next()){
        
            if(table->getString(1) == tableName){
                
                return true;
            
            }
        }
        delete state;
        delete table;
    }
    catch(SQLException &e){

        cout << "SQL EXCEPTION " << e.what() << endl;
        cout << "SQLState" << e.getSQLState() << endl;

    }
    return false;
}

bool ORM::checkIfDatabaseExists(string dbName){
    try{

        Statement* state = this->connection->createStatement();
        string query =  "SHOW DATABASES";

        ResultSet* databaseName = state->executeQuery(query);

        while(databaseName->next()){
        
            if(databaseName->getString(1) == dbName){
                
                return true;
            
            }
        }

        delete state;
        delete databaseName;

    }
    catch(SQLException &e){

        cout << "SQL EXCEPTION " << e.what() << endl;
        cout << "SQLState" << e.getSQLState() << endl;

    }
    
    return false;

};

Connection* ORM::connect(){
    if(presetOrCustomSettings()){
    
        return  createConnection(this->connectionProps);
    
    }
    else{

        return  createConnection(getPropertiesFromUser());
    
    };
    
}

Connection* ORM::createConnection(vector<string> connectionProperties){
    
    try{

        
        string connectionAddr = connectionProperties[CONNECTION_STRING];
        string username = connectionProperties[USERNAME];
        string password = connectionProperties[PASSWORD];
        string database = connectionProperties[DBNAME];


        this->connection = driver->connect(connectionAddr , username , password );
        if(! this->checkIfDatabaseExists(database) ){
            char choice;
            
            cout << "Database Doesnt not Exists!\nPress y or Y to create a new Database with the name " << database << "\n" ;
            
            cin >> choice;
            
            if(choice == 'Y' || choice == 'y'){
                
                this->createDatabaseIfNotExists(database);
                cout << "\nDatabase Created Successfully\n";
            
            }
        }
        // this->createDatabaseIfNotExists(database);
        this->connection->setSchema(database);

        if(this->connection){

            // cout << "\n Connected";
            system("clear");
            return this->connection;
        }
    }
    catch(SQLException &e){
        cout << "SQL EXCEPTION " << e.what() << endl;
        cout << "SQLState" << e.getSQLState() << endl;
    }
    return 0;
};



ResultSet* ORM::raw(string query){
    Connection *rawConn;
    
    // delete this->statement;
    rawConn = this->connect();

    this->statement = rawConn->createStatement();

    return this->statement->executeQuery(query);

}


string ORM::parseSingleString(ResultSet *str){
    string result; 
    
    while(str->next()){
    
        result = str->getString(1);
    
    }
    
    return result;
}


void ORM::insert(string tablename , string columns , string values){
    try{
        string query = "INSERT INTO "+tablename+" ( "+columns+" )"+" VALUES ( " + values + " );";  
    
        int rowAffected = 0;

        Connection *rawConn;
        
        rawConn = this->connect();

        this->statement = rawConn->createStatement();

        this->statement->execute(query);
        
        rowAffected  = this->statement->getUpdateCount();
        
        // cout << rowAffected;  

        if(rowAffected == 1){
      
            system("clear");
 
            cout << "\n Record Created Successfully\n"; 
        }
        else{
 
            throw SQLException("Error Creating Record");
 
        }

    }
    catch(SQLException& e){
        cerr << "\n SQLEXCEPTION: " << e.what() << "\n"; 
    };
    
    
    

}