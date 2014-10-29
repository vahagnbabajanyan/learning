#ifndef _IMPORTER_HPP_
#define _IMPORTER_HPP_

#include <QObject>

class importer : public QObject
{
        Q_OBJECT;
public:
        static importer& instance()
        {
                static importer theObject;
                return theObject;
        }
private:
        importer()
        {}
        importer(const importer&);
        importer& operator=(const importer&);
};

#endif
