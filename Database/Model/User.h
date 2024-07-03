#include "../ORM.h"
const int INSERTFLAG = 4;
const int FETCHFLAG = 5;
class User : public ORM {
    private:
        string username;
        string password;

    public:

        // string getUserNameFromDB(string username);
        string getPasswordFromDB(string username);
        void   insertUserinDB(string username , string password);
        bool authenticateUser(string username , string password);
        bool checkIfUserExistsInDB(string username);

};


