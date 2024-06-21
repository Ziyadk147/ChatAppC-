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
//segfault refactor
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

bool ORM::presetOrCustomConnectionProperties(){
    system("clear");
    int choice;
    cout << "Select \n1)PreDefined Database Settings\n2)Give Custom Settings\n";
    cin >> choice;

    if(choice == 1){
        this->connectionProps = {"tcp://127.0.0.1:3306" , "ziyad" , "root" , "chatapp"};
        // this->connectionProps = tempVector;

        return true;
        
    }
    else{
        return false;
    }

};
Connection* ORM::createConnection(vector<string> connectionProperties){
    
    try{

        string connectionAddr = connectionProperties[CONNECTION_STRING];
        string username = connectionProperties[USERNAME];
        string password = connectionProperties[PASSWORD];
        string database = connectionProperties[DBNAME];


        this->connection = driver->connect(connectionAddr , username , password );
        
        this->connectionProps = connectionProperties;

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

            cout << "\n Connected";
            return this->connection;
    
        }
    }
    catch(SQLException &e){
    
        cout << "SQL EXCEPTION " << e.what() << endl;
        cout << "SQLState" << e.getSQLState() << endl;
    
    }
    return 0;
};

ResultSet* ORM::rawQuery(string query){
    Statement* stmt;
    try{
        if(presetOrCustomConnectionProperties()){
            
           
            this->createConnection(this->connectionProps);   


        }
        else{
            this->createConnection(this->getPropertiesFromUser());

        
        }
        
        stmt = this->connection->createStatement();
    
    }
    catch(SQLException& e){

        cerr << "SQL EXCEPTION " << e.what() << "\n";
        cerr << "SQLState" << e.getSQLState() << "\n";
    
    }
    return stmt->executeQuery(query);

}

ResultSet* ORM::where(string columns , string tablename , string operand1 , string sqlOperator , string operand2){ 
    
        string query = "SELECT "+columns+" FROM "+tablename+" WHERE "+operand1 +" "+sqlOperator+" "+"'"+operand2+"'";
  
        // cout << query;
  
        return this->rawQuery(query);
    
         
};
string ORM::parseSingleString(ResultSet* result){
    while(result->next()){
 
        return result->getString(1);
 
    }
    return "";
    // delete result;
};