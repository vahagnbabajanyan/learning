#ifndef IMPORTER_HPP
#define IMPORTER_HPP

#include <QObject>
#include <QString>

namespace core
{

// importer object to be used when user will choose file to import
// object will be created wnd moved in new thread
class importer : public QObject
{
        Q_OBJECT;
public:
        importer(const QString& fileName, const QString& tblName);

public slots:
        void import();
signals:
        void finishedImporting();
private:
        QString _fileName;
        QString _tblName;

};

} // end of namespace core

#endif
