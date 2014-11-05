#include <QString>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

#include "reader.hpp"

reader::reader(const QString& fileName)
        : _file(fileName)
{
        if (_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
                _stream.setDevice(&_file);
        }
}

std::pair<bool, QString> reader::getNext()
{
        while (_lineWords.isEmpty() && !_stream.atEnd()) {
                split(_stream.readLine());
        }
        if (_lineWords.isEmpty()) {
                return std::make_pair(false, "");
        }
        QString next = _lineWords.front();
        next = next.trimmed();
        _lineWords.pop_front();
        if (!next.isEmpty() && next.size() > 1) {
                return std::make_pair(true, next);
        } else {
                return getNext();
        }
}

void reader::split(const QString& line)
{
        QRegExp rx("([^\\w])");
        _lineWords = line.split(rx);
        _lineWords.removeDuplicates();
}
