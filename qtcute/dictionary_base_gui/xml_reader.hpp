#ifndef _XML_READER_HPP_
#define _XML_READER_HPP_

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QString>

#include <list>
#include <string>

#include "user_settings.hpp"
#include "app_settings.hpp"

namespace settings
{

class xmlReader
{
public:
        xmlReader();
        bool createDomDocument(const QString& fileName);
        bool getAppSettings(appSettings& aset);
        bool getUserSettings(const std::string& user, userSettings& usets);
private:
        bool prepareUser(const std::string& user);

        bool initUserSettings(const QDomElement &element, userSettings &usets);
        bool initUserDictionaries(const QDomElement &element, userSettings &usets);
        bool initUserTests(const QDomElement &element, userSettings &usets);
        bool initUserLevel(const QDomElement &element, userSettings &usets);
        bool initUserStatistics(const QDomElement &element, userSettings &usets);

        bool initAppSettings(const QDomElement &element, appSettings &asets);

        QFile _file;
        QDomDocument* _dom;
};

}

#endif
