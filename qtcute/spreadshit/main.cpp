#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        MainWindow *window = new MainWindow;
        window->show();
        app.exec();
}
