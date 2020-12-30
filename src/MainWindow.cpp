#include "SystemTray.h"
#include "ui_MainWindow.h"
#include "Boards_ui.h"
#include "Undo.h"
#include "WBoard.h"

extern Undo undo;
extern File MainFile;

#include <QToolBar>
#include <QFont>
#include <QLabel>
#include <QLayout>
#include <QStringLiteral>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     VisibleCentralWidgetIndx(0),
     ui(new Ui::MainWindow),
     boardIsShown(-1)
{
    stack = new QStackedWidget;

    SystemTray::instance(this);

    boards = new Boards_ui(this);
    board = nullptr;

    stack->addWidget(boards);

    setCentralWidget(stack);

    toolBar = createToolBar();
    addToolBar(Qt::TopToolBarArea, toolBar);

    setAutoFillBackground(true);
    QPalette pall;
    pall.setColor(this->backgroundRole() , Qt::white);
    setPalette(pall);
    setMinimumSize(850, 650);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QToolBar* MainWindow::createToolBar()
{
   QToolBar* qtb = new QToolBar("Tool Bar");
   qtb->setAutoFillBackground(true);

   QPalette pall;
   pall.setColor(qtb->backgroundRole() , Qt::white);
   qtb->setPalette(pall);
   qtb->setMovable(false);
   qtb->setIconSize(QSize(50, 50));

   QWidget* wgt = new QWidget(this);
   QHBoxLayout* qhbxl = new QHBoxLayout();
   QLabel* lbl = new QLabel("To-do-app");
   lbl->setAlignment(Qt::AlignCenter);
   QFont font = lbl->font();
   font.setPixelSize(30);
   lbl->setFont(font);
   lbl->setStyleSheet(QStringLiteral("color: blue"));
   qhbxl->addWidget(lbl, 1);
   wgt->setLayout(qhbxl);

   qtb->addSeparator();
   qtb->addAction(QPixmap(":/images/home8.png"), "homepage", this, SLOT(slotHome()));
   qtb->addSeparator();
   qtb->addAction(QPixmap(":/images/undo1.png"), "undo", this, SLOT(slotUndo()));
   qtb->addSeparator();
   qtb->addWidget(wgt); //
   qtb->addSeparator();
   qtb->addAction(QPixmap(":/images/plus6.png"), "add board", boards, SLOT(slotAddBoard()));
   qtb->addSeparator();
   qtb->addAction(QPixmap(":/images/info2.png"), "information", boards, SLOT(slotInfo()));
   qtb->addSeparator();

   return qtb;
}

void MainWindow::slotUndo()
{
    if (!undo.restored())
    {
        restore();

        if (VisibleCentralWidgetIndx)
        {
            stack->removeWidget(board);
            delete board;
        }

        MainFile.open("data/mainfile.txt", File::create);
        stack->removeWidget(boards);
        delete boards;
        MainFile.seekg(std::ios::beg);
        boards = new Boards_ui(this);

        stack->addWidget(boards);

        undo = Undo();

        removeToolBar(toolBar);
        toolBar = createToolBar();
        addToolBar(Qt::TopToolBarArea, toolBar);

        if (VisibleCentralWidgetIndx)
        {
            board = new WBoard(boards->get_child(boardIsShown), this);
            stack->addWidget(board);
            stack->setCurrentIndex(1);
        }
    }
}

void MainWindow::slotHome()
{
    if (board)
    {
        stack->removeWidget(board);
        delete board;
        board = nullptr;
        VisibleCentralWidgetIndx = 0;
        boardIsShown = -1;
    }
}

void MainWindow::slotPressed(Component* brd, std::size_t indx)
{
    board = new WBoard(brd, this);
    stack->addWidget(board);
    stack->setCurrentIndex(1);
    VisibleCentralWidgetIndx = 1;
    boardIsShown = indx;
}

void MainWindow::slotBoardChanged(Component* brd)
{
    stack->removeWidget(board);
    delete board;
    board = new WBoard(brd, this);
    stack->addWidget(board);
    stack->setCurrentIndex(1);
}


