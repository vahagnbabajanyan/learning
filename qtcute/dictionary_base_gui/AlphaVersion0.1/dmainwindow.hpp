#ifndef _DMAINWINDOW_HPP_
#define _DMAINWINDOW_HPP_

#include <QMainWindow>
#include <QKeySequence>

#include <string>

#include "user_gui.hpp"
#include "import_file.hpp"
// #include "dictionay_window.hpp" instead used below QDialog

class QAction;
class QMenu;
class QToolBar;
class QDialog;
class QLabel;
class FindDialog;
class Spreadsheet;

namespace gui
{

class dMainWindow : public QMainWindow
{
        Q_OBJECT;
private:
        enum RecentFileCount { MaxRecentFiles = 5 };
public:
        dMainWindow();

private slots:
        void newFile();
        void openFile();
        bool saveFile();
        bool saveAsFile();
        void openImportDialog();
        void openExportDialog();
        void openRecentFile();
        void openMergeDialog();
        void deleteFile();
        void openInsertDialog();
        void logUser(const std::string& user);

        void startImportingSlot(const QString&, const QString&);
signals:
        void startImportingSignal(const QString&, const QString&);

private:
        void createActions();
        QAction* createAction(const std::string&, QKeySequence, const std::string&);
        void createMenus();
        void createToolBars();

private:
        // shoud be user defined type dictionary_window
        loginUser *_loginUser;
        userMenu *_userMenu;
        QDialog *_exportDialog;
        importFileDialog *_importDialog;
        QDialog *_mergeDialog;
        QDialog *_insertDialog;
        QDialog *_recentFilesDialog;

        // File menu bar actions
        QAction *_newAction;
        QAction *_openAction;
        QAction *_saveAction;
        QAction *_saveAsAction;
        QAction *_importAction;
        QAction *_exportAction;
        QAction *_recentFilesAction[MaxRecentFiles];

        // Edit menu bar actions active only when any dictionary is opened
        QAction *_mergeToAction;
        QAction *_deleteAction;
        QAction *_insertAction;

        // Help menu bar actions
        QAction *_about;

        QMenu *_fileMenu;
        QMenu *_editMenu;
        QMenu *_helpMenu;

        QToolBar *_newToolBar;
        QToolBar *_editToolBar;

};

} // end of namespace gui

#endif
