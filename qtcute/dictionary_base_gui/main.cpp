#include <QApplication>

#include "dmainwindow.hpp"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        gui::dMainWindow *dict = new gui::dMainWindow;
        dict->show();
        app.exec();
}
