#ifndef _IMPORTER_HPP_
#define _IMPORTER_HPP_

#include <QWidget>

class importer : public QWidget
{
        Q_OBJECT;
public:
        importer(QWidget* owner = 0);

private:
        QWidget* _loading;
};

#endif
