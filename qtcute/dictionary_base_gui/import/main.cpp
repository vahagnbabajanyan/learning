#include <QApplication>
#include <QDebug>

#include "importer.hpp"
#include "my_thread.hpp"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);

        importer imp;
        imp.show();

        app.exec();
}
