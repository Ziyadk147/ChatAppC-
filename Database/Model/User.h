#include "../ORM.h"

class User : public ORM {
    private:
        int user_id;
        string username;
        string password;

    public:

        // string getUserNameFromDB(string username);
        string getPasswordFromDB(string username);
        void   insertUserinDB(string username , string password);
        bool authenticateUser(string username , string password);
        bool checkIfUserExistsInDB(string username);

        void setUserName(string username);
        void setPassword(string username);    

        int getUserID(string username);

        string getUserName();
};


