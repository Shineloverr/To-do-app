#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include "MainWindow.h"

#include <QSystemTrayIcon>
#include <QtWidgets>
#include <iostream>
#include <QTime>
#include <QTimer>

class SystemTray : public QWidget
{
    Q_OBJECT

public slots:
    void slotShowMessage(const std::string& message)
    {
       sysTray->showMessage("To-so-app", QString::fromUtf8(message.data(), message.size()), QSystemTrayIcon::Information, 1000000);
    }

    void slotShowHide()
    {
        if (mw->isHidden())
        {
            mw->show();
        }
        else
        {
            mw->hide();
        }
    }

public:
    SystemTray(MainWindow* mwindow, QWidget* parent = nullptr)
        :  QWidget(parent),
          mw(mwindow)
    {
        if (QSystemTrayIcon::supportsMessages())
        {
        mw->setWindowTitle("To do app");

        sysTray = new QSystemTrayIcon(this);
        sysTray->setIcon(QPixmap(":/images/plus6.png"));
        sysTray->setToolTip("To do app");

        QAction* pactQuit = new QAction("&Quit", this);
        connect(pactQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

        QAction* pactShowHide = new QAction("&Show/Hide Application Window", this);
        connect(pactShowHide, SIGNAL(triggered()), this, SLOT(slotShowHide()));

        m = new QMenu(this);
        m->addAction(pactQuit);
        m->addAction(pactShowHide);

        sysTray->setContextMenu(m);
        sysTray->show();
        }
    }

    static SystemTray* instance(MainWindow* mw = nullptr)
    {
        static SystemTray* ins = nullptr;
        if (ins == nullptr)
             ins = new SystemTray(mw);

        return ins;
    }

protected:
    virtual void closeEvent(QCloseEvent* event) override
    {
        if (sysTray->isVisible())
        {
            hide();
        }
    }

private:
    MainWindow* mw;
    QMenu* m;
    QSystemTrayIcon* sysTray;
};

#endif // SYSTEMTRAY_H


