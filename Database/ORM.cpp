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

Connection* ORM::createConnection(){
    
    try{
        
        string connectionAddr = getConnectionString();
        string username = getDBUsername();
        string password = getDBPassword();
        string database = getDBName();

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
    // delete this->statement;
    if(!this->connection){

        this->createConnection();
    
    }


    this->statement = this->connection->createStatement();

    // delete rawConn;
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

        if(!this->connection){

            this->createConnection();
        
        }


        this->statement = this->connection->createStatement();

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

int ORM::parseSingleInt(ResultSet *str){
    int result;
    
    while(str->next()){
    
        result = str->getInt(1);
    
    }   
    
    return result;
}