#ifndef _IMPORTER_HPP_
#define _IMPORTER_HPP_

#include <QWidget>
#include "my_thread.hpp"

class importer : public QWidget
{
        Q_OBJECT;
public:
        importer(QWidget* owner = 0);

private slots:
        void drawTable();
        void drawLoading();

private:
        QString _tableName;
        myThread *_th;
};

#endif
