#include <QApplication>

#include "dmainwindow.hpp"
#include "core_manager.hpp"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        gui::dMainWindow *dict = new gui::dMainWindow;
        core::coreManager manager;
        QObject::connect(dict, SIGNAL(startImportingSignal(const QString&, const QString&)), &manager, SLOT(startImportingHandler(const QString&, const QString&)));
        dict->setFixedSize(800, 500);
        dict->show();
        app.exec();
}
