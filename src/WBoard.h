#ifndef WBOARD_H
#define WBOARD_H

#include <QtWidgets>
#include "Component.h"
#include "MainWindow.h"

class WBoard : public QWidget
{
    Q_OBJECT

public:
    explicit WBoard(Component* brd, MainWindow* p = nullptr);

signals:
    void signalChanged(Component* brd);

public slots:
    void slotAddList();
    void slotRemoveList(std::size_t);
    void slotListChanged();

private:
    QLabel* label();
    Component* board;
    QPushButton* addButton;
    MainWindow* parent;
};

#endif // WBOARD_H
