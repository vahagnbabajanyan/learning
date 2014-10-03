#ifndef _USER_HPP_
#define _USER_HPP_

#include <QWidget>
#include <QDialog>
#include <QString>

struct userInfo
{
        std::string _name;
        std::string _lastname;
        std::string _nickname;
        std::string _password;
        std::string _xmlPath;
};

class user
{
private:
        int _count;
};

class userRegisterDialog : public QDialog
{};

class userLoginDialog : public QWidget
{};

#endif
