#include <QFile>
#include <QDebug>
#include <QDomNode>
#include <QDomElement>
#include <QDomText>
#include <QString>
#include <QTextStream>

#include <iostream>
#include <map>
#include <list>
#include <string>

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
                std::cerr << "Error : Parse error at line " << errorLine << ", "
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
                std::cerr << "Error : Wrong structure of xml file" << std::endl;
                return false;
        }
        while (!child.isNull()) {
                if (user.c_str() != child.toElement().tagName()) {
                        initUserSettings(child.toElement(), usets);
                        return true;
                }
                child = child.nextSibling();
        }
        std::cerr << "Error : Can't find such user : " << user << std::endl;
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
        QDomElement root = addBlankUser(usets._user);
        if (!root.isNull()) {
                std::list<std::string> l;
                l.push_back("dictionaty1");
                l.push_back("dictionaty2");
                l.push_back("dictionaty3");
                addDictionaries(root, l);
                // addTests(root, usets._tests);
                // addLevel(root, usets._level);
                // addPassword(root, usets._level);
        }
        serializeDomDocumentChanges();
        return true;
}

QDomElement xmlRW::addBlankUser(const std::string& user)
{
        QDomElement root = _dom->documentElement();
        if (root.tagName() != "root_dictionary_application") {
                std::cerr << "Error : Not a root element of application" << std::endl;
                return QDomElement();
        }
        QDomNode child = findTagByName(root, "users");
        QDomElement userElem = _dom->createElement("user");
        child.toElement().appendChild(userElem);
        userElem.setAttribute("name", user.c_str());
        addBlankElement(userElem, "dictionaries");
        addBlankElement(userElem, "tests");
        addBlankElement(userElem, "statistics");
        addBlankElement(userElem, "settings");
        return userElem;
}

QDomElement xmlRW::addBlankElement(QDomNode root, const std::string& tagName)
{
        QDomElement blank = _dom->createElement(tagName.c_str());
        blank.appendChild(_dom->createTextNode(""));
        root.appendChild(blank);
        return blank;
}

bool xmlRW::serializeDomDocumentChanges()
{
        QString xml = _dom->toString(8);
        QString tmp = _fileName + "_serialized";
        QFile file(tmp);
        if (!file.open(QFile::ReadWrite | QFile::Text)) {
                std::cerr << "Error : Cannot open file " << qPrintable(tmp)
                        << ": " << qPrintable(file.errorString()) << std::endl;
                return false;
        }
        QTextStream out(&file);
        out << xml;
        return true;
}

QDomNode xmlRW::findTagByName(const QDomElement& root, const std::string& tagName, const atributes &attrs) const
{
        QDomNode child = root.firstChild();
        while (!child.isNull() && 0 != tagName.compare(child.toElement().tagName().toUtf8().constData())) {
                child = child.nextSibling();
        }
        if (0 == tagName.compare(child.toElement().tagName().toUtf8().constData())) {
                return child;
        }
        return QDomNode();
}

QDomNode xmlRW::findTagByPath(const QDomElement& root, const std::string& path, const atributes &attrs) const
{
        std::string npath = path;
        std::string tagName = getNextTagName(npath);
        if (tagName.empty()) {
                // throw exception
                return QDomNode();
        }
        if (npath.empty()) {
                return findTagByName(root, tagName);
        } else {
                QDomNode nextRoot = findTagByName(root, tagName);
                if (!nextRoot.isNull()) {
                        findTagWithSpecifiedAttributes();
                        return findTagByPath(nextRoot.toElement(), npath, attrs);
                }
        }
        // throw exception
        return QDomNode();
}

std::string xmlRW::getNextTagName(std::string& npath)
{
        std::string tagName;
        std::string::size_type pos = npath.find_first_of(",");
        if (std::string::npos != pos) {
                tagName = npath.substr(0, pos);
                npath.erase(0, pos + 1);
                npath = QString(npath.c_str()).trimmed().toUtf8().constData();
        } else {
                npath = QString(npath.c_str()).trimmed().toUtf8().constData();
                if (npath.empty()) {
                        return std::string();
                }
                tagName = npath;
                npath.clear();
        }
        return tagName;
}

void xmlRW::addDictionaries(const QDomElement& root, const std::list<std::string>& dictionaries)
{
        QDomNode dnode = findTagByName(root, "dictionaries");
        if (dnode.isNull()) {
                //throw exception
                std::cerr << "ERROR : can't find tag with name dictionaries" << std::endl;
                return;
        }
        std::list<std::string>::const_iterator it = dictionaries.begin();
        while ( dictionaries.end() != it ) {
                QDomElement delem = addBlankElement(dnode, "dictionary");
                dnode.appendChild(delem);
                delem.appendChild(_dom->createTextNode((*it).c_str()));
                ++it;
        }
}

void xmlRW::addDictionary(const std::string& user, const std::string& dictionary)
{
        QDomElement root = getRoot();
        QDomNode n = findTagByPath(root, "users");
}

/*void xmlRW::addTagToRoot(const QDomElement& root, const std::string& childName,
                const std::string& tagName, std::map<std::string, std::string>& attrs)
{
        QDomNode dnode = findTagByName(root, childName);
        if (dnode.isNull()) {
                //throw exception
                std::cerr << "ERROR : can't find tag with name : " << tagName << std::endl;
                return;
        }
        QDomElement delem = addBlankElement(dnode, tagName);
        dnode.appendChild(delem);
        delem.appendChild(_dom->createTextNode((*it).c_str()));
        ++it;

}*/

/*void xmlRW::addTests(const QDomElement& root, usets._tests)
{}

void xmlRW::addLevel(const QDomElement& root, usets._level)
{}

void xmlRW::addPassword(const QDomElement& root, usets._level)
{}
*/

} // end of namespace settings
