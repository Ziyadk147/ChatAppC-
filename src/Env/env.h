#ifndef ENV_H
#define ENV_H

#include<iostream>
#include <fstream>
#include<map>

using namespace std;


class Environment {
    private:
        map<string , string> envDict;

        string trim(const string& message);

        map <string , string> env(string& filename);

    public:
        Environment(){
            string filename = ".env";
            env(filename);
        }
        Environment(string filename){
            env(filename);
        }
        string getConnectionString();
        string getDBUsername();
        string getDBPassword();
        string getDBName();

};



#endif