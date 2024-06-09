
#include "BaseMigration.cpp"
#include <vector>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql;

class MessagesTable : protected Migration{
    private:
        string columns = "id INT AUTO_INCREMENT PRIMARY KEY, message VARCHAR(255) NOT NULL,sender_id INT ,receiver_id INT ";
        string table = "messages"; 
    public:
        MessagesTable(){

            create(this->table , this->columns);
        
        }
};
