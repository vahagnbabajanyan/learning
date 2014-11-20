#ifndef _XML_READER_HPP_
#define _XML_READER_HPP_

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QString>

#include <list>
#include <string>
#include <map>

#include "user_settings.hpp"
#include "app_settings.hpp"

namespace settings
{

class xmlRW
{
public:
        typedef std::map<std::string, std::string> atributes;
public:
        static xmlRW& instance()
        {
                static xmlRW theObject;
                return theObject;
        }
        bool createDomDocument(const QString& fileName);
        bool getAppSettings(appSettings& aset);
        bool getUserSettings(const std::string& user, userSettings& usets);

        bool addUser(const userSettings& usets);
        QDomElement addBlankUser(const std::string& user);
        void addDictionaries(const QDomElement&, const std::list<std::string>&);

        QDomElement getRoot()
        {
                return _dom->documentElement();
        }
        QDomNode findTagByPath(const QDomElement&, const std::string&, const atributes& = atributes()) const;
private:
        xmlRW();
        xmlRW(const xmlRW&);
        xmlRW& operator=(const xmlRW&);
private:
        static std::string getNextTagName(std::string&);
        QDomElement addBlankElement(QDomNode, const std::string&);
        bool prepareUser(const std::string& user);
        QDomNode findTagByName(const QDomElement&, const std::string&, const atributes& = atributes()) const;
        bool initUserSettings(const QDomElement &element, userSettings &usets);
        bool initUserDictionaries(const QDomElement &element, userSettings &usets);
        bool initUserTests(const QDomElement &element, userSettings &usets);
        bool initUserLevel(const QDomElement &element, userSettings &usets);
        bool initUserStatistics(const QDomElement &element, userSettings &usets);
        bool initAppSettings(const QDomElement &element, appSettings &asets);
        bool serializeDomDocumentChanges();
private:
        QString _fileName;
        QDomDocument* _dom;
};

}

#endif
