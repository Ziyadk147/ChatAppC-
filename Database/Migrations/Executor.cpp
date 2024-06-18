#include <iostream>
#include "../Migrations/BaseMigration.h"
using namespace std;


int main (){
    BaseMigration migrations;
    migrations.migrate("messages" , "id INT PRIMARY KEY AUTO_INCREMENT , messages VARCHAR(255) , sender_id INT , receiver_id INT "); 
    migrations.migrate("users" , "id INT PRIMARY KEY AUTO_INCREMENT , username VARCHAR(255) , password VARCHAR(255)"); 

    // d14 16127
    
    
}