#ifndef _USER_GUI_HPP_
#define _USER_GUI_HPP_

#include <QWidget>
#include <QTableWidget>
#include <QSpacerItem>

#include <iostream>
#include <string>
#include <vector>

#include "user.hpp"

class QLabel;
class QLineEdit;
class QPushButton;

namespace gui
{

class loginUser : public QWidget
{
        Q_OBJECT;
public:
        loginUser(QWidget* w = 0);
        userInfo getUserInfo();
private:
        void createUserPart();
        void createPasswordPart();
        bool inputIsValid();
        bool checkUserInformation(std::string& err);
        void login();
private slots:
        void submitOkButton();
        void createNewUser();
signals:
        void loggedIn(const std::string& user);
private:
        QLabel *_userIdLabel;
        QLabel *_userPassLabel;
        QLineEdit *_userIdLine;
        QLineEdit *_userPassLine;
        QPushButton* _okButton;
        QPushButton* _newUserButton;
};

class userMenu : public QWidget
{
        Q_OBJECT;
public:
        userMenu(const std::string& user, QWidget* w = 0);
private slots:
        void showDictionaryList();
        void showStatistics();
        void showSettings();
        void showTests();
private:

private:
        QWidget *_mainWidget;
        std::list<QWidget*> _widgets;
        QPushButton *_userStatisticsButton;
        QPushButton *_userDictionariesButton;
        QPushButton *_userTestsButton;
        QPushButton *_userSettingsButton;

        QWidget *_userStats;
        QTableWidget *_userDicts;
        QTableWidget *_userTests;
        QWidget *_userSetts;

        QWidget *_visibleWidget;

        QSpacerItem *_spacer;
};

} // end of namespace gui

#endif
