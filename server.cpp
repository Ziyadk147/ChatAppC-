#include <iostream>
#include <vector>
#include "Database/ORM.h"

using namespace std;


int main(){

    ORM Test;
    Test.createConnection(Test.getPropertiesFromUser());//gets the input from the user and creates a connection


}