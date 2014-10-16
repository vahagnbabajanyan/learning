#include <QFile>
#include <QDomNode>
#include <QDomElement>
#include <QString>

#include <iostream>

#include "xml_reader.hpp"

namespace settings
{

xmlReader::xmlReader()
        : _dom(new QDomDocument)
{
}

bool
xmlReader::createDomDocument(const QString& fileName)
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
xmlReader::getAppSettings(appSettings &asets)
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
xmlReader::initAppSettings(const QDomElement &element, appSettings &asets)
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
xmlReader::getUserSettings(const std::string& user, userSettings& usets)
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
xmlReader::initUserSettings(const QDomElement& element, userSettings &usets)
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
xmlReader::initUserDictionaries(const QDomElement &element, userSettings &usets)
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
xmlReader::initUserTests(const QDomElement &element, userSettings &usets)
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
xmlReader::initUserStatistics(const QDomElement &element, userSettings &usets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()){
                usets._stats = child.toElement().text().toUtf8().constData();
                child = child.nextSibling();
        }
        return true;
}

bool
xmlReader::initUserLevel(const QDomElement &element, userSettings &usets)
{
        QDomNode child = element.firstChild();
        while (!child.isNull()) {
                if ("level" == child.toElement().tagName()) {
                        QDomNode levelNode = child.toElement().firstChild();
                        usets._level = levelNode.toElement().tagName().toUtf8().constData();
                }
                child = child.nextSibling();
        }
        return true;
}

} // end of namespace settings
