#include <iostream>

#include <QtGui>
#include <QDialog>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "mainwindow.hpp"

MainWindow::MainWindow()
{
        QDialog *_dialog = new QDialog;
        setCentralWidget(_dialog);

        createActions();
        createMenus();
//        createContextMenu();
//        createToolBars();
//        createStatusBar();

//        readSettings();

        _findDialog = 0;
        setWindowIcon(QIcon(":/images/icon.png"));
//        setCurrentFile("");
}

void MainWindow::createActions()
{
        _newAction = new QAction(tr("&New"), this);
        _newAction->setShortcut(QKeySequence::New);
        _newAction->setStatusTip("Create a new app file");
        connect(_newAction, SIGNAL(triggered()), this, SLOT(newFile()));

        _saveAction = new QAction("&Save", this);
        _saveAction->setShortcut(QKeySequence::Save);
        _saveAction->setStatusTip("Save application");
        connect(_saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
}

void MainWindow::createMenus()
{
        _fileMenu = menuBar()->addMenu("&File");
        _fileMenu->addAction(_newAction);
        _fileMenu->addAction(_saveAction);
}

void MainWindow::newFile()
{
        std::cout << "Creating new file" << std::endl;
}

bool MainWindow::save()
{
        std::cout << "Saving File" << std::endl;
        return true;
}

void MainWindow::open()
{
        std::cout << "Opening File" << std::endl;
}
