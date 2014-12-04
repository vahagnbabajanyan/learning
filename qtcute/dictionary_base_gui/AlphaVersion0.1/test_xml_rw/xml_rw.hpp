#ifndef XML_RW_HPP
#define XML_RW_HPP

#include <QDomDocument>
#include <QString>

#include <map>

namespace settings
{

class xmlPath
{

};

class xmlReadWrite
{
// singleton inplementation
// {
public:
        static xmlReadWrite& instance()
        {
                static xmlReadWrite theObject;
                return theObject;
        }

        bool createDomDocument(const QString& fileName);
private:
        xmlReadWrite();
        xmlRearWrite(const xmlReadWrite&);
        xmlReadWrite& operator=(const xmlReadWrite&);
// }
// singleton inplementation

public:
        QDomNode findTagByPath();
private:
private:
        QDomDocument *dom;
        QString _fileName;

};

} // end of xmlspace settings

#endif
