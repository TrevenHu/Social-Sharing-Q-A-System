#include <QApplication>
#include "mainwindow.h"
#include <Class.h>
#include <login.h>
vector<User>userVec;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    userVec.clear();
    vector<User>::iterator iter;
    iter=userVec.begin();
    User u1("h","1");
    User u2("z","2");
    User u3("y","3");
    userVec.push_back(u1);
    userVec.push_back(u2);
    userVec.push_back(u3);
    Login login;
    if(login.exec()==QDialog::Accepted)
    {
        return a.exec();
    }
    else return 0;
}
