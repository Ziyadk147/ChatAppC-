#include "../Database/ORM.h"

#include<iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <vector>

using namespace std;
using namespace sql;
class Migration : protected ORM{
    private:
        Connection* initiateConnection(){
    
    
                return createConnection(ORM::getPropertiesFromUser());
        
        }
    protected:
        vector<string> connectionProperties;        

    public:    
        
        void create(string TableName , string columns){
            Connection *connection = this->initiateConnection();
            Statement *statement = connection->createStatement();
            
            string query = "CREATE TABLE "+TableName+"("+columns+")";

            statement->execute(query);


            cout << "Table " <<TableName <<" Created Successfully!";
            delete statement;
            delete connection;            
        }


};
