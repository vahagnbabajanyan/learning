#include <iostream>
#include <fstream>
#include <string>

#include <QStringList>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
/*        QStringList propertyNames;
        QStringList propertyKeys;

        QString strReply = (QString)reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObject = jsonResponse.object();

        QJsonArray jsonArray = jsonObject["properties"].toArray();

        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();

            propertyNames.append(obj["PropertyName"].toString());
            propertyKeys.append(obj["key"].toString());
        }
        */

class jsonReader
{
public:
        jsonReader(const std::string jsonString)
        {
                _json = QJsonDocument::fromJson(jsonString.c_str());
        }

        bool getVerbs(QStringList& verbs)
        {
                QJsonValue val;
                if (getValueByPath("verb", val)) {
                        QJsonValue values = val.toArray().at(1);
                        if (values.isArray()) {
                                foreach (QJsonValue vv, values.toArray()) {
                                        verbs.push_back(vv.toString());
                                }
                        }
                        return true;
                }
                return false;
        }

        bool getNouns(QStringList& nouns)
        {
                QJsonValue val;
                if (getValueByPath("noun", val)) {
                        QJsonValue values = val.toArray().at(1);
                        if (values.isArray()) {
                                foreach (QJsonValue vv, values.toArray()) {
                                        nouns.push_back(vv.toString());
                                }
                        }
                        return true;
                }
                return false;
        }
private:
        bool getValueByPath(const QString& path ,QJsonValue& val)
        {
                if (_json.isArray()) {
                        QJsonArray arr = _json.array();
                        QJsonValue val = arr.at(1);
                        if (val.isArray()) {
                                QJsonArray a1 = val.toArray();
                                foreach (QJsonValue v1, a1) {
                                        if (v1.isArray()) {
                                                QJsonArray a2 = v1.toArray();
                                                foreach (QJsonValue v2, a2) {
                                                        if (v2.isArray()) {
                                                                std::cout << "OMJ" << std::endl;
                                                        } else {
                                                                if (path == v2.toString()) {
                                                                        val = v1;
                                                                        return false;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
                return false;
        }

private:
        QJsonDocument _json;
};


int main()
{
        QString path = "1, verb";
        const std::string fname = "test.js";
        std::ifstream fin;
        fin.open(fname.c_str());
        if (!fin.good()) {
                return 1;
        }
        std::string content = std::string();
        while (!fin.eof()) {
                std::string tmp;
                std::getline(fin, tmp);
                content += tmp;
        }

        QString qs(content.c_str());
        QJsonDocument json = QJsonDocument::fromJson(content.c_str());


/*        QJsonValue val = getValueByPath(json, "verb");

        QJsonValue key = val.toArray().at(0);
        std::cout << "KeyValue : " << qPrintable(key.toString()) << " :: ";
        QJsonValue values = val.toArray().at(1);
        if (values.isArray()) {
                foreach (QJsonValue vv, values.toArray()) {
                        std::cout << qPrintable(vv.toString()) << " ";
                }
        }

        std::cout << std::endl;

        if (json.isArray()) {
                QJsonArray arr = json.array();
                QJsonValue val = arr.at(1);
                if (val.isArray()) {
                        QJsonArray a1 = val.toArray();
                        foreach (QJsonValue v1, a1) {
                                if (v1.isArray()) {
                                        QJsonArray a2 = v1.toArray();
                                        foreach (QJsonValue v2, a2) {
                                                if (v2.isArray()) {
                                                        std::cout << "OMJ" << std::endl;
                                                } else {
                                                        std::cout << qPrintable(v2.toString()) << std::endl;
                                                }
                                        }
                                }
                        }
                }
        }
             if (val.isObject()) {
                        std::cout << "  Object : " << std::endl;
                } else if (val.isArray()) {
                        QJsonArray a = val.toArray();
                        std::cout << "  Array : " << a.size() << std::endl;
                        foreach (QJsonValue v1, a) {
                                if (v1.isObject()) {
                                        std::cout << "          isObject" << std::endl;
                                } else if (v1.isArray()) {
                                        QJsonArray a1 = v1.toArray();
                                        std::cout << "          isArray : " << a1.size() << std::endl;
                                        foreach (QJsonValue v2, a1) {
                                                if (v2.isArray()) {
                                                        std::cout << "                  isArray" << std::endl;
                                                } else {
                                                        std::cout << "                  isObject : " << qPrintable(v2.toString()) << std::endl;
                                                }
                                        }
                                }
                        }
                }
        } else if (json.isObject()) {
                std::cout << "is object" << std::endl;
                QJsonObject obj = json.object();
        }
        */
}
