#include <QFile>
#include <QDomNode>
#include <QDomElement>
#include <QDomText>
#include <QString>
#include <QTextStream>

#include <iostream>

#include "xml_reader.hpp"

namespace settings
{

xmlRW::xmlRW()
        : _dom(new QDomDocument)
{
}

bool
xmlRW::createDomDocument(const QString& fileName)
{
        QFile file(fileName);
        if (!file.open(QFile::ReadWrite | QFile::Text)) {
                std::cerr << "Error : Cannot open file " << qPrintable(fileName)
                        << ": " << qPrintable(file.errorString()) << std::endl;
                return false;
        }

        QString errorStr;
        int errorLine;
        int errorColumn;

        if (!_dom->setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
                std::cout << "Error : Parse error at line " << errorLine << ", "
                        << "column : " << errorColumn << ": "
                        << qPrintable(errorStr) << std::endl;
                return false;
        }
        return true;
}

bool
xmlRW::getAppSettings(appSettings &asets)
{
        QDomElement root = _dom->documentElement();
        if (root.tagName() != "root_dict") {
                std::cerr << "Error : Not a root element of application" << std::endl;
                return false;
        }
        QDomNode child = root.firstChild();
        while (!child.isNull()) {
                if ("appconfig" == child.toElement().tagName()) {
                        initAppSettings(child.toElement(), asets);
                }
                child = child.nextSibling();
        }

        return true;
}

bool
xmlRW::initAppSettings(const QDomElement &element, appSettings &asets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()) {
                if ("url" == child.toElement().tagName()) {
                        asets._url = child.toElement().text().toUtf8().constData();
                }
                child = child.nextSibling();
        }
        return true;
}

bool
xmlRW::getUserSettings(const std::string& user, userSettings& usets)
{
        QDomElement root = _dom->documentElement();
        if (root.tagName() != "root_dict") {
                std::cerr << "Error : Not a root element of application" << std::endl;
                return false;
        }
        QDomNode child = root.firstChild();
        while (!child.isNull() && "users" != child.toElement().tagName()) {
                child = child.nextSibling();
        }
        child = child.toElement().firstChild();
        if ("user" != child.toElement().tagName()) {
                std::cout << "Error : Wrong structure of xml file" << std::endl;
                return false;
        }
        while (!child.isNull()) {
                if (user.c_str() != child.toElement().tagName()) {
                        initUserSettings(child.toElement(), usets);
                        return true;
                }
                child = child.nextSibling();
        }
        std::cout << "Error : Can't find such user : " << user << std::endl;
        return false;
}

bool
xmlRW::initUserSettings(const QDomElement& element, userSettings &usets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()) {
                if ("dictionaries" == child.toElement().tagName()) {
                        initUserDictionaries(child.toElement(), usets);
                } else if ("tests" == child.toElement().tagName()) {
                        initUserTests(child.toElement(), usets);
                } else if ("settings" == child.toElement().tagName()) {
                        initUserLevel(child.toElement(), usets);
                } else if ("statistics" == child.toElement().tagName()) {
                        initUserStatistics(child.toElement(), usets);
                }
                child = child.nextSibling();
        }
        return true;
}

bool
xmlRW::initUserDictionaries(const QDomElement &element, userSettings &usets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()) {
                if ("dictionary" != child.toElement().tagName()) {
                        continue;
                }
                usets._dictionaries.push_back(child.toElement().text().toUtf8().constData());
                child = child.nextSibling();
        }
        return true;
}

bool
xmlRW::initUserTests(const QDomElement &element, userSettings &usets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()) {
                if ("test" != child.toElement().tagName()) {
                        continue;
                }
                usets._tests.push_back(child.toElement().text().toUtf8().constData());
                child = child.nextSibling();
        }
        return true;

}

bool
xmlRW::initUserStatistics(const QDomElement &element, userSettings &usets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()){
                usets._stats = child.toElement().text().toUtf8().constData();
                child = child.nextSibling();
        }
        return true;
}

bool
xmlRW::initUserLevel(const QDomElement &element, userSettings &usets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()) {
                if ("level" == child.toElement().tagName()) {
                        QDomNode levelNode = child.toElement().firstChild();
                        usets._level = userSettings::levelFromString(levelNode.toElement().tagName().toUtf8().constData());
                }
                child = child.nextSibling();
        }
        return true;
}

// editing xml document
bool xmlRW::addUser(const userSettings& usets)
{
        QDomElement root = addUser(usets._user);
        if (!root.isNull()) {
                // addDictionaries(root, usets._dictionaries);
                // addTests(root, usets._tests);
                // addLevel(root, usets._level);
                // addPassword(root, usets._level);
        }
        return true;
}

QDomElement xmlRW::addUser(const std::string& user)
{
        std::cout << "adding user" << std::endl;
        QDomElement root = _dom->documentElement();
        if (root.tagName() != "root_dictionary_application") {
                std::cerr << "Error : Not a root element of application" << std::endl;
                return QDomElement();
        }
        QDomNode child = root.firstChild();
        while (!child.isNull() && "users" != child.toElement().tagName()) {
                child = child.nextSibling();
        }
        QDomElement userElem = _dom->createElement("user");
        child.toElement().appendChild(userElem);
        userElem.setAttribute("name", user.c_str());
        addBlankElement(userElem, "dictionaries");
        addBlankElement(userElem, "tests");
        addBlankElement(userElem, "statistics");
        addBlankElement(userElem, "settings");
        serializeDomDocumentChanges();
        return userElem;
}

void xmlRW::addBlankElement(QDomNode root, const std::string& tagName)
{
        QDomElement blank = _dom->createElement(tagName.c_str());
        blank.appendChild(_dom->createTextNode(""));
        root.appendChild(blank);
}

bool xmlRW::serializeDomDocumentChanges()
{
        QString xml = _dom->toString(4);
        QString tmpFileForSerialization = _fileName + "_serialized";
        QFile file(tmpFileForSerialization);
        if (!file.open(QFile::ReadWrite | QFile::Text)) {
                std::cerr << "Error : Cannot open file " << qPrintable(tmpFileForSerialization)
                        << ": " << qPrintable(file.errorString()) << std::endl;
                return false;
        }
        QTextStream out(&file);
        out << xml;
        return true;
}

void xmlRW::addDictionaries(root, usets._dictionaries)
{}

void xmlRW::addTests(root, usets._tests)
{}

void xmlRW::addLevel(root, usets._level)
{}

void xmlRW::addPassword(root, usets._level)
{}


} // end of namespace settings
