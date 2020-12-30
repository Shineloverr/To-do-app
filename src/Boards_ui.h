#ifndef BOARDS_UI_H
#define BOARDS_UI_H

#include "Board.h"
#include "Widget_Board.h"

#include <QtWidgets>
#include <QInputDialog>
#include <vector>

class MainWindow;

class Boards_ui : public QWidget
{
    Q_OBJECT

public:
    Boards_ui(MainWindow* parent = nullptr);
    Component* get_child(std::size_t indx)
    {
        if (indx < contents.size())
        {
            return contents[indx].get();
        }

        return nullptr;
    }

    QWidget* create_board_ui(std::size_t indx, const std::string& label);
    QWidget* add();

    virtual ~Boards_ui() override;

public slots:
    void slotEditBoard(std::size_t, const std::string&);
    void slotRemoveBoard(std::size_t);
    void slotAddBoard();
    void slotInfo();
    void slotPressed(std::size_t);

signals:
    void signalPressed(Component* brd, std::size_t indx);

private:
    QGridLayout* lout;
    std::size_t row;
    std::size_t column;
    std::vector<QWidget*> boards;
    std::vector<std::shared_ptr<Component>> contents;
};

#endif // BOARDS_UI_H
