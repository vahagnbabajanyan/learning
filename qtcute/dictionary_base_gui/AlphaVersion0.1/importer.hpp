#ifndef IMPORTER_HPP
#define IMPORTER_HPP

#include <QObject>
#include <QString>

// importer object to be used when user will choose file to import
// object will be created wnd moved in new thread
class importer : public QObject
{
        Q_OBJECT;
public:
        importer(const QString& fileName, const QString& tblName);
        void import()
        {
                // create reader object : reader.hpp
                // read all words till end of file : reader.hpp
                // connect google.translate every 2 minutes : connector.hpp
                // parse answer as much as possible : json_parse.hpp
                // save answer in txt file : serializeTxt TODO to implement
                // imsert parsed version in mysql DB : sql_engine.hpp
        }
private:
        QString _fileName;
        QString _tblName;

};

#endif
