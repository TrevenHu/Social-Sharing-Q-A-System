#include "user.h"
#include "vector"
#include <QString>
using namespace std;
using std::vector;
class User
{
    public:
        User(string _user_id,string _password)
        {
            user_id=_user_id;
            password=_password;
        };
        User(string user);
        string Getuser_id(User _user)
        {
            string id;
            id=_user.user_id;
            return id;
        }
        void add_focus(string id)
        {
            focuslist.push_back(id);
        }
        bool operator==(const User& u)const
        {
            return u.user_id==user_id&&u.password==password;
        }
        string user_id;
        string password;
        vector<string>focuslist;

};


