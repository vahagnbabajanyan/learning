#include "json_reader.hpp"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringList>

namespace net
{

jsonReader::jsonReader(const std::string jsonString)
{
        _json = QJsonDocument::fromJson(jsonString.c_str());
}

void jsonReader::getWordsForKey(const std::string& key, QStringList& words)
{
        std::list<QJsonValue> values;
        getValueByPath(key.c_str(), _json.array(), values);
        if (values.size() > 0) {
                std::cout << "found JsonValue" << std::endl;
                if (values.begin()->isArray()) {
                        std::cout << "ERROR root should be array" << std::endl;
                        QJsonArray jwords = values.begin()->toArray().at(1).toArray();
                        foreach(QJsonValue wordNode, jwords) {
                                words.push_back(wordNode.toString());
                        }
                }
        }
}

void jsonReader::getValueByPath(QString key, QJsonArray root, std::list<QJsonValue>& values)
{
        foreach(QJsonValue v, root) {
                if (v.isArray()) {
                        getValueByPath(key, v.toArray(), values);
                } else if (key == v.toString()) {
                        values.push_back(root);
                }
        }
}

} // end of namespace net
