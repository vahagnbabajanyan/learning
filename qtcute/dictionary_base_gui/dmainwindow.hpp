#ifndef _DMAINWINDOW_HPP_
#define _DMAINWINDOW_HPP_

#include <QMainWindow>
// #include "dictionay_window.hpp" instead used below QDialog

class QAction;
class QMenu;
class QDialog;
class QLabel;
class FindDialog;
class Spreadsheet;

namespace gui
{

class dMainWindow : public QMainWindow
{
        Q_OBJECT;
public:
        dMainWindow()
        {
                _dictionary_window = new QDialog;
                setCentralWidget(_window);

                createActions();
        }
private slots:
private:
        void createActions();
        void createMenus();
private:
        // shoud be user defined type dictionary_window
        QDialog *_dictionary_window;
        QDialog *_exportDialog;
        QDialog *_importDialog;
        QDialog *_mergeDialog;
        QDialog *_insertDialog;
        QDialog *_recentFilesDialog;

        // File menu bar actions
        QAction *_openAction;
        QAction *_saveAction;
        QAction *_saveAsAction;
        QAction *_importAction;
        QAction *_exportAction;
        QAction *_recentFiles;

        // Edit menu bar actions active only when any dictionary is opened
        QAction *_mergeToAction;
        QAction *_deleteAction;
        QAction *_insertAction;

        // Help menu bar actions
        QAction *_about;

        QMenu *_fileMenu;
        QMenu *_editMenu;
        QMenu *_helpMenu;
}

} // end of namespace gui

#endif
