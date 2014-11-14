#ifndef _JSON_READER_HPP_
#define _JSON_READER_HPP_

#include <iostream>
#include <fstream>
#include <string>

#include <QStringList>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QObject>

namespace net
{

class jsonReader : public QObject
{
        Q_OBJECT
public:
        jsonReader(const std::string jsonString);
        void getWordsForKey(const std::string& key, QStringList& words);

private:
        void getValueByPath(QString key, QJsonArray root, std::list<QJsonValue>& values);

private:
        QJsonDocument _json;
};

} // end of namespace net

#endif
