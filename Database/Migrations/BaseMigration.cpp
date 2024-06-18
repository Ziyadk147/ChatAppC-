#include "../Migrations/BaseMigration.h"


Connection* BaseMigration::initiateConnection(){

    if(this->connectionProperties.empty()){

        this->connectionProperties =  getPropertiesFromUser();

    }

    return createConnection(this->connectionProperties);

};

void BaseMigration::migrate(string tableName , string columns){
    try{
        Connection* connection = this->initiateConnection();
        
        Statement* statement = connection->createStatement();



        string query = "CREATE TABLE IF NOT EXISTS "+ tableName +" ( "+columns+" )";

        if(!checkIfTableExists(tableName)){

            statement->execute(query);
            cout << "\nTable "+tableName+" Successfully Created!\n ";        
        
        }
        else{
            cout << "\nTable Already Exists...skipping...\n";
        }
        
        delete statement;
        delete connection;

    }
    catch(SQLException& error){
        cerr << "SQL EXCEPTION : " << error.what() << "\n";
        cerr << "SQLSTATE: " << error.getSQLState() << "\n";
    }            
}
