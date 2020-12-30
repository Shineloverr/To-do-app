#include "Undo.h"
#include "Board.h"
#include "Checklist.h"
#include "Text.h"
#include "MainWindow.h"
#include "SystemTray.h"

File MainFile("data/mainfile.txt");
Undo undo;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    SystemTray::instance(&mw);
    mw.show();
    QApplication::setQuitOnLastWindowClosed(false);
    return a.exec();
}

