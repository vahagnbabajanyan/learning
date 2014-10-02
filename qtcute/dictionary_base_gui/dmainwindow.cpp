#include <string>

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QDialog>
#include <QString>

#include "dmainwindow.hpp"

namespace gui
{

dMainWindow::dMainWindow()
{
        _dictionary_window = new QDialog;
        setCentralWidget(_dictionary_window);

        createActions();
        createMenus();
        createToolBars();
}

QAction*
dMainWindow::createAction(const std::string& actionName, QKeySequence scut, const std::string& tip)
{
        QAction* tmp = new QAction(actionName.c_str(), this);
        tmp->setShortcut(scut);
        tmp->setStatusTip(tr(tip.c_str()));
        return tmp;
}

void
dMainWindow::createActions()
{
        _newAction = createAction("&New", QKeySequence::New, "New dictionary");
        connect(_newAction, SIGNAL(triggered()), this, SLOT(newFile()));
        _openAction = createAction("&Open", QKeySequence::Open, "Open dictionary");
        connect(_openAction, SIGNAL(triggered()), this, SLOT(openFile()));
        _saveAction = createAction("&Save", QKeySequence::Save, "Save dictionary");
        connect(_saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
        _saveAsAction = createAction("&SaveAs", QKeySequence::SaveAs, "Save dictionary as");
        connect(_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsFile()));
        _importAction = createAction("Import", QKeySequence::UnknownKey, "Import text file");
        connect(_importAction, SIGNAL(triggered()), this, SLOT(openImportDialog()));
        _exportAction = createAction("Export", QKeySequence::UnknownKey, "Export dictionary to text file");
        connect(_exportAction, SIGNAL(triggered()), this, SLOT(openExportDialog()));
        for ( int i = 0; i < MaxRecentFiles; ++i) {
                _recentFilesAction[i] = new QAction(this);
                _recentFilesAction[i]->setVisible(false);
                connect(_recentFilesAction[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
        }
        _mergeToAction = createAction("MergeTo", QKeySequence::UnknownKey, "Merge current dictionary to another one");
        connect(_mergeToAction, SIGNAL(triggered()), this, SLOT(openMergeDialog()));
        _deleteAction = createAction("Delete", QKeySequence::UnknownKey, "Delete current dictionary");
        connect(_deleteAction, SIGNAL(triggered()), this, SLOT(deleteFile()));
        _insertAction = createAction("Insert", QKeySequence::UnknownKey, "Insert dictionary to current");
        connect(_insertAction, SIGNAL(triggered()), this, SLOT(openInsertDialog()));
}

void
dMainWindow::createMenus()
{
        _fileMenu = menuBar()->addMenu(tr("&File"));
        _fileMenu->addAction(_newAction);
        _fileMenu->addAction(_openAction);
        _fileMenu->addSeparator();
        _fileMenu->addAction(_saveAction);
        _fileMenu->addAction(_saveAsAction);
        _fileMenu->addSeparator();
        _fileMenu->addAction(_importAction);
        _fileMenu->addAction(_exportAction);
        for (int i = 0; i < MaxRecentFiles; ++i) {
                _fileMenu->addAction(_recentFilesAction[i]);
        }
        _editMenu = menuBar()->addMenu(tr("&Tools"));
        _editMenu->addAction(_mergeToAction);
        _editMenu->addAction(_insertAction);
        _editMenu->addSeparator();
        _editMenu->addAction(_deleteAction);

        _helpMenu = menuBar()->addMenu(tr("&Help"));
}

void
dMainWindow::createToolBars()
{
        _newToolBar = addToolBar("&File");
        _newToolBar->addAction(_newAction);
        _newToolBar->addAction(_openAction);
        _newToolBar->addAction(_saveAction);
}

void dMainWindow::newFile()
{}
void dMainWindow::openFile()
{}
bool dMainWindow::saveFile()
{
        return true;
}
bool dMainWindow::saveAsFile()
{
        return false;
}
void dMainWindow::openImportDialog()
{}
void dMainWindow::openExportDialog()
{}
void dMainWindow::openRecentFile()
{}
void dMainWindow::openMergeDialog()
{}
void dMainWindow::deleteFile()
{}
void dMainWindow::openInsertDialog()
{}

} // end of namespace gui
