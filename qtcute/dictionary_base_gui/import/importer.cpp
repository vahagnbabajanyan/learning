#include "importer.hpp"
#include "reader/reader.hpp"
#include "my_thread.hpp"

#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>

importer::importer(QWidget* owner)
        : QWidget(owner)
{
        QFileDialog *fd = new QFileDialog(this);
        fd->setNameFilter("Text Files (*.txt)");
        fd->show();
        if (fd->exec()) {
                QString fileName = fd->selectedFiles().front();
                _tableName = fileName;
                _th = new myThread(fileName, _tableName);
                connect(_th, SIGNAL(finished()), this, SLOT(drawTable()), Qt::DirectConnection);
                connect(_th, SIGNAL(started()), this, SLOT(drawLoading()), Qt::DirectConnection);
                _th->start();
        }
}

void importer::drawLoading()
{
        QWidget *loading = new QWidget;
        loading->setFixedSize(250, 200);
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->addWidget(loading);
}

void importer::drawTable()
{
        qDebug() << "drawing table in thread " << QThread::currentThreadId();
}
