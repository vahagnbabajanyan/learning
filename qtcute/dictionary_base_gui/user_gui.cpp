#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

#include "user_gui.hpp"

namespace gui
{

// Implementation loginUser

loginUser::loginUser(QWidget* w)
        : QWidget(w)
{
        std::cout << "creating loginUser" << std::endl;
        createUserPart();
        createPasswordPart();
        _okButton = new QPushButton(tr("OK"));
        connect(_okButton, SIGNAL(clicked()), this, SLOT(submitOkButton()));
        _newUserButton = new QPushButton(tr("New User"));
        connect(_newUserButton, SIGNAL(clicked()), this, SLOT(createNewUser()));
        QGridLayout *formGridLayout = new QGridLayout;
        formGridLayout->addWidget( _userIdLabel, 0, 0 );
        formGridLayout->addWidget( _userIdLine, 0, 1 );
        formGridLayout->addWidget( _userPassLabel, 1, 0 );
        formGridLayout->addWidget( _userPassLine, 1, 1 );
        formGridLayout->addWidget( _okButton, 2, 1 );
        formGridLayout->addWidget( _newUserButton, 3, 1 );
        setLayout(formGridLayout);
}

userInfo
loginUser::getUserInfo()
{
        userInfo info;
        info._name = "Vahagn";
        return info;
}

void
loginUser::createUserPart()
{
        _userIdLabel = new QLabel(tr("UserId"));
        _userIdLine = new QLineEdit;
        _userIdLabel->setBuddy(_userIdLine);
}

void
loginUser::createPasswordPart()
{
        _userPassLabel = new QLabel(tr("Password"));
        _userPassLine = new QLineEdit;
        _userPassLabel->setBuddy(_userPassLine);
}

bool
loginUser::inputIsValid()
{
        return true;
}

bool
loginUser::checkUserInformation(std::string& err)
{
        err = "";
        return true;
}

void
loginUser::submitOkButton()
{
        if (inputIsValid()) {
                std::string error;
                if (!checkUserInformation(error)) {
                        //mark input invalid output error message
                }
                login();
        }
}

void
loginUser::login()
{
        // load user information
        // create dictionary
        //      set paths for user
        // mark as loged in
}

void
loginUser::createNewUser()
{
        std::cout << "createNewUser" << std::endl;
}

// Implementation of class userMenu

userMenu::userMenu(const std::string& user, QWidget* w)
        : QWidget(w)
{
        QLabel *userLabel = new QLabel(tr(user.c_str()));
        _userStatisticsButton = new QPushButton(tr("Statistics"));
        _userDictionariesButton = new QPushButton(tr("Dictionaries"));
        _userTestsButton = new QPushButton(tr("Tests"));
        _userSettingsButton = new QPushButton(tr("Settings"));
        QGridLayout *gridLayout = new QGridLayout;
        gridLayout->addWidget(userLabel, 0, 0);
        gridLayout->addWidget(_userStatisticsButton, 1, 0);
        gridLayout->addWidget(_userDictionariesButton, 2, 0);
        gridLayout->addWidget(_userTestsButton, 3, 0);
        gridLayout->addWidget(_userSettingsButton, 4, 0);
        _userStats = 0;
        _userDicts = 0;
        _userTests = 0;
        _userSetts = 0;
        setLayout(gridLayout);
}

} // end of namespace gui

