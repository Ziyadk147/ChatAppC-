#ifndef BASEMIGRATION_H
#define BASEMIGRATION_H

#include<iostream>
#include "../ORM.h"



class BaseMigration : public ORM {

    private:

        vector <string> connectionProperties;

        Connection* initiateConnection();

    public:

        void migrate(string tableName , string columns);


};
#endif