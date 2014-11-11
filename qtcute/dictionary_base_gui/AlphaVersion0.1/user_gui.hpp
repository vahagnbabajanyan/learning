#ifndef _USER_GUI_HPP_
#define _USER_GUI_HPP_

#include <QWidget>
#include <QTableWidget>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <iostream>
#include <string>
#include <vector>

#include "user.hpp"
#include "user_settings.hpp"

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

class extendableMenu : public QWidget
{
Q_OBJECT
public:
        enum Type
        {
                DICT = 0,
                TEST = 1,
                STAT = 2,
                SETT = 3
        };
public:
        extendableMenu(const settings::userSettings* setts);
private:
        std::list<QPushButton*> _buttons;
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
        void createButtons();
        void setConnections();
        void setMenuLayout(QLabel*, QVBoxLayout*&);

        template <typename W>
        void showHideWidget(W*& w, QPushButton* button)
        {
                if (0 != _visibleWidget) {
                        _visibleWidget->hide();
                        _mainWidget->layout()->removeWidget(_visibleWidget);
                }
                if (0 == _visibleWidget || w != _visibleWidget) {
                        w = new W;
                        w->setFixedSize(145, 140);
                        std::list<QWidget*>::iterator it = std::find(_widgets.begin(), _widgets.end(), button);
                        int indx = std::distance(_widgets.begin(), it) + 2;
                        static_cast<QHBoxLayout*>(_mainWidget->layout())->insertWidget(indx, w);
                        _visibleWidget = w;
                        _spacer->changeSize(5, 88);
                        return;
                }
                _visibleWidget = 0;
                _spacer->changeSize(5, 240);
        }

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
        QTableWidget *_userSetts;

        QWidget *_visibleWidget;

        QSpacerItem *_spacer;
};

} // end of namespace gui

#endif
