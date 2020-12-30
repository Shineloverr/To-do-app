#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMessageBox>
#include <QStackedWidget>

#include "Boards_ui.h"

class SystemTray;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QToolBar* createToolBar();

    ~MainWindow();

public slots:
    void slotPressed(Component* brd, std::size_t indx);
    void slotHome();
    void slotUndo();
    void slotBoardChanged(Component* brd);

private:
    bool VisibleCentralWidgetIndx;
    QStackedWidget* stack;
    Boards_ui* boards;
    QWidget* board;
    QToolBar* toolBar;
    Ui::MainWindow *ui;
    int boardIsShown;
};
#endif // MAINWINDOW_H
