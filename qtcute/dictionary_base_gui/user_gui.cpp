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

// Implementation of class userMenu

userMenu::userMenu(const std::string& user, QWidget* w)
        : QWidget(w), _visibleWidget(0)
{
        QLabel *userLabel = new QLabel(tr(user.c_str()));
        // creating buttons
        _userStatisticsButton = new QPushButton(tr("Statistics"));
        connect(_userStatisticsButton, SIGNAL(clicked()), this, SLOT(showStatistics()));
        _widgets.push_back(_userStatisticsButton);
        _userDictionariesButton = new QPushButton(tr("Dictionaries"));
        connect(_userDictionariesButton, SIGNAL(clicked()), this, SLOT(showDictionaryList()));
        _widgets.push_back(_userDictionariesButton);
        _userTestsButton = new QPushButton(tr("Tests"));
        connect(_userTestsButton, SIGNAL(clicked()), this, SLOT(showTests()));
        _widgets.push_back(_userTestsButton);
        _userSettingsButton = new QPushButton(tr("Settings"));
        connect(_userSettingsButton, SIGNAL(clicked()), this, SLOT(showSettings()));
        _widgets.push_back(_userSettingsButton);

        // create mainWidget
        _mainWidget = new QWidget;
        _mainWidget->setFixedSize(110, 400);

        QVBoxLayout *menuLayout = new QVBoxLayout;
        menuLayout->addWidget(userLabel, 0, 0);
        menuLayout->addWidget(_userStatisticsButton, 1, 0);
        menuLayout->addWidget(_userDictionariesButton, 2, 0);
        menuLayout->addWidget(_userTestsButton, 3, 0);
        menuLayout->addWidget(_userSettingsButton, 4, 0);
        _spacer = new QSpacerItem(5, 250);
        menuLayout->addItem(_spacer);
        _mainWidget->setLayout(menuLayout);
        QHBoxLayout *mainLayout = new QHBoxLayout;
        mainLayout->addWidget(_mainWidget);
        setLayout(mainLayout);
}

void
userMenu::showDictionaryList()
{
        if (0 != _visibleWidget) {
                _visibleWidget->hide();
                _mainWidget->layout()->removeWidget(_visibleWidget);
        }
        if (0 == _visibleWidget || _userDicts != _visibleWidget) {
                _userDicts = new QTableWidget;
                _userDicts->setFixedSize(100, 180);
                std::list<QWidget*>::iterator it = std::find(_widgets.begin(), _widgets.end(), _userDictionariesButton);
                int indx = std::distance(_widgets.begin(), it) + 2;
                static_cast<QHBoxLayout*>(_mainWidget->layout())->insertWidget(indx, _userDicts);
                _visibleWidget = _userDicts;
                _spacer->changeSize(5, 50);
                return;
        }
        _visibleWidget = 0;
        _spacer->changeSize(5, 250);
}

void
userMenu::showTests()
{
        if (0 != _visibleWidget) {
                _visibleWidget->hide();
                _mainWidget->layout()->removeWidget(_visibleWidget);
        }
        if (0 == _visibleWidget || _userTests != _visibleWidget) {
                _userTests = new QTableWidget;
                _userTests->setFixedSize(100, 180);
                std::list<QWidget*>::iterator it = std::find(_widgets.begin(), _widgets.end(), _userTestsButton);
                int indx = std::distance(_widgets.begin(), it) + 2;
                static_cast<QHBoxLayout*>(_mainWidget->layout())->insertWidget(indx, _userTests);
                _visibleWidget = _userTests;
                _spacer->changeSize(5, 50);
                return;
        }
        _visibleWidget = 0;
        _spacer->changeSize(5, 250);
}


void
userMenu::showSettings()
{
        if (0 != _visibleWidget) {
                _visibleWidget->hide();
                _mainWidget->layout()->removeWidget(_visibleWidget);
        }
        if (0 == _visibleWidget || _userSetts != _visibleWidget) {
                _userSetts = new QTableWidget;
                _userSetts->setFixedSize(100, 180);
                std::list<QWidget*>::iterator it = std::find(_widgets.begin(), _widgets.end(), _userSettingsButton);
                int indx = std::distance(_widgets.begin(), it) + 2;
                static_cast<QHBoxLayout*>(_mainWidget->layout())->insertWidget(indx, _userSetts);
                _visibleWidget = _userSetts;
                _spacer->changeSize(5, 50);
                return;
        }
        _visibleWidget = 0;
        _spacer->changeSize(5, 250);

}

void
userMenu::showStatistics()
{
        if (0 != _visibleWidget) {
                _visibleWidget->hide();
                _mainWidget->layout()->removeWidget(_visibleWidget);
        }
        if (0 == _visibleWidget || _userStats != _visibleWidget) {
                _userStats = new QTableWidget;
                _userStats->setFixedSize(100, 180);
                std::list<QWidget*>::iterator it = std::find(_widgets.begin(), _widgets.end(), _userStatisticsButton);
                int indx = std::distance(_widgets.begin(), it) + 2;
                static_cast<QHBoxLayout*>(_mainWidget->layout())->insertWidget(indx, _userStats);
                _visibleWidget = _userStats;
                _spacer->changeSize(5, 50);
                return;
        }
        _visibleWidget = 0;
        _spacer->changeSize(5, 250);
}

} // end of namespace gui

