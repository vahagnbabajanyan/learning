#include <QApplication>

#include <iostream>

#include "xml_reader.hpp"
#include "user_settings.hpp"

int main()
{
        settings::xmlRW::instance().createDomDocument("test.xml");
        QDomElement root = settings::xmlRW::instance().getRoot();
        QDomNode node = settings::xmlRW::instance().findTagByPath(root, "users, user, dictionaries, dictionary");
        if (!node.isNull()) {
                std::cout << "tagName: " << node.toElement().tagName().toUtf8().constData() << std::endl;
        }
        /*settings::userSettings u("Hrayr");
        settings::xmlRW::instance().addUser(u);*/
}
