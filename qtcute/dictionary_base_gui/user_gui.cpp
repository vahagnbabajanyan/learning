#include <iterator>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>

#include "user_gui.hpp"

namespace gui
{

// Implementation loginUser

loginUser::loginUser(QWidget* w)
        : QWidget(w)
{
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
        QWidget* centralLoginWidget = new QWidget;
        centralLoginWidget->setFixedSize(250, 200);
        centralLoginWidget->setLayout(formGridLayout);
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->addWidget(centralLoginWidget);
        setLayout(mainLayout);
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
        /*if (inputIsValid()) {
                std::string error;
                if (!checkUserInformation(error)) {
                        //mark input invalid output error message
                }*/
                login();
       // }
}

void
loginUser::login()
{
        emit loggedIn("Vahagn");
        // emit sugnal
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


// Implementation of class extendableMenu
extendableMenu::extendableMenu(const userSettings* setts, Type t)
{

}





// Implementation of class userMenu

userMenu::userMenu(const std::string& user, QWidget* w)
        : QWidget(w), _visibleWidget(0)
{
        createButtons();
        setConnections();
        _spacer = new QSpacerItem(5, 240);
        QVBoxLayout *menuLayout = new QVBoxLayout;
        QLabel *userLabel = new QLabel(tr(user.c_str()));
        setMenuLayout(userLabel, menuLayout);
        _mainWidget = new QWidget;
        _mainWidget->setFixedSize(130, 400);
        _mainWidget->setLayout(menuLayout);
        QHBoxLayout *mainLayout = new QHBoxLayout;
        mainLayout->addWidget(_mainWidget);
        setLayout(mainLayout);
}

void
userMenu::createButtons()
{
        _userStatisticsButton = new QPushButton(tr("Statistics"));
        _widgets.push_back(_userStatisticsButton);
        _userDictionariesButton = new QPushButton(tr("Dictionaries"));
        _widgets.push_back(_userDictionariesButton);
        _userTestsButton = new QPushButton(tr("Tests"));
        _widgets.push_back(_userTestsButton);
        _userSettingsButton = new QPushButton(tr("Settings"));
        _widgets.push_back(_userSettingsButton);
}

void
userMenu::setConnections()
{
        connect(_userStatisticsButton, SIGNAL(clicked()), this, SLOT(showStatistics()));
        connect(_userDictionariesButton, SIGNAL(clicked()), this, SLOT(showDictionaryList()));
        connect(_userTestsButton, SIGNAL(clicked()), this, SLOT(showTests()));
        connect(_userSettingsButton, SIGNAL(clicked()), this, SLOT(showSettings()));
}

void
userMenu::setMenuLayout(QLabel *label, QVBoxLayout *&menuLayout)
{
        menuLayout->addWidget(label, 0, 0);
        menuLayout->addWidget(_userStatisticsButton, 1, 0);
        menuLayout->addWidget(_userDictionariesButton, 2, 0);
        menuLayout->addWidget(_userTestsButton, 3, 0);
        menuLayout->addWidget(_userSettingsButton, 4, 0);
        menuLayout->addItem(_spacer);
}

void
userMenu::showTests()
{
        showHideWidget<QTableWidget>(_userTests, _userTestsButton);
}

void
userMenu::showDictionaryList()
{
        showHideWidget<QTableWidget>(_userDicts, _userDictionariesButton);
}

void
userMenu::showStatistics()
{
        showHideWidget<QWidget>(_userStats, _userStatisticsButton);
}

void
userMenu::showSettings()
{
        showHideWidget<QTableWidget>(_userSetts, _userSettingsButton);
}

} // end of namespace gui
