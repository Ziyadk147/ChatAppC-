#include "../Database/ORM.h"

class User : public ORM {
    private:
        string username;
        string password;

    public:
        string getUserNameFromDB();
        string getPasswordFromDB();

        
}