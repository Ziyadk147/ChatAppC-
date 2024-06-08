#include <iostream>

#include "Database/ORM.h"
using namespace std;


int main(){

    ORM Test;
    string properties[4] = {"tcp://127.0.0.1:3306" , "ziyad" , "root" , "test"};
    Test.createConnection(properties);

}