#ifndef _READER_HPP_
#define _READER_HPP_

#include <QString>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QTextStream>
#include <map>
#include <iostream>

class reader
{
public:
        reader(const QString& fileName);
        std::pair<bool, QString> getNext();

private:
        void split(const QString& line);

private:
        QFile _file;
        QTextStream _stream;
        QStringList _lineWords;
};

#endif
