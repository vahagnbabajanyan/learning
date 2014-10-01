#include <QAction>

#include "dmainwindow.hpp"

namespace gui
{

dMainWindow::dMainWindow()
{
        _dictionary_window = new QDialog;
        setCentralWidget(_window);

        createActions();
}

dMainWindow::createaActions()
{
        _newAction = new QAction(tr("&New"), this);
        _newAction->setShortcut(QKeySequence::New);
        _newAction->setStatusTip(tr("New dictionary"));

        _openAction = new QAction(tr("&Open"), this);
        _openAction->setShortcut(QKeySequence::Open);
        _openAction->setStatusTip(tr("Open dictionary"));
        // connect triggered to openFile slot
}

} // end of namespace gui
