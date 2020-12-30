#include "Boards_ui.h"
#include "Widget_Board.h"
#include "Undo.h"
#include "MainWindow.h"

#include <QInputDialog>
#include <QMessageBox>

#include <iostream>

extern File MainFile;
extern Undo undo;

Boards_ui::Boards_ui(MainWindow* parent /* = nullptr */)
    : QWidget(parent),
      row(0),
      column(0)
{
    load_contents(contents);

    lout = new QGridLayout();

    QWidget* wgt;
    for (std::size_t i = 0; i < contents.size(); i++)
    {
        wgt = create_board_ui(i, contents[i]->get_label());
        lout->addWidget(wgt, row, column++);
        boards.emplace_back(wgt);


        if (column == 3)
        {
            column = 0;
            row++;
        }
    }
    wgt = Widget_Board::create_ADD_widget(this);

    lout->addWidget(wgt, row, column++);
    boards.emplace_back(wgt);

    if (column == 3)
    {
        column = 0;
        row++;
    }

    this->setLayout(lout);

    connect(this, SIGNAL(signalPressed(Component*, std::size_t)), parent, SLOT(slotPressed(Component*, std::size_t)));
}

Boards_ui::~Boards_ui()
{
     undo.~Undo();
     MainFile.open("data/mainfile.txt", File::create);
     std::cout << "Boards_ui destructor\n";
}

QWidget* Boards_ui::create_board_ui(std::size_t indx, const std::string &label)
{
    return new Widget_Board(indx, label, this);
}

void Boards_ui::slotAddBoard()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter board name:", QLineEdit::Normal, "Board", &bOk);

    if (bOk)
    {
        std::cout << "slotAddBoard ok\n";

        if (!column)
        {
            column = 2;
            row--;
        }
        else
        {
            column--;
        }

        add_board(contents, str.toStdString());
        QWidget* wgt = create_board_ui(contents.size() - 1, str.toStdString());
        lout->addWidget(wgt, row, column++);
        boards.emplace_back(wgt);

        if (column == 3)
        {
            column = 0;
            row++;
        }

        wgt = Widget_Board::create_ADD_widget(this);      

        lout->addWidget(wgt, row, column++);
        boards.emplace_back(wgt);

        if (column == 3)
        {
            column = 0;
            row++;
        }
    }
}

void Boards_ui::slotInfo()
{
    QMessageBox::information(nullptr, "How to use", "djfklsssssssssssssssssss\n"
                                                     "ssssssssssssssssssssssssss\n"
                                                     "sssssssssssssssssssssssssss\n"
                                                     "ssssssssssssssssssssssssssss\n"
                                                     "ssssssssssssssssssssssssssss\n"
                                                     "ssssssssssssssssssssssssssss\n"
                                                     "ssssssssssssssssssssssssssss\n"
                                                     "ssssssssssssssssssssssssssss\n"
                                                     "sssssssklgklfkglkflgjifljgkf\n"
                                                     "jgklfjkglgjkfjgkfjkgjfklg");
}

void Boards_ui::slotEditBoard(std::size_t indx, const std::string& lbl)
{
    set_label(contents, indx, lbl);
}

void Boards_ui::slotPressed(std::size_t indx)
{
    emit signalPressed(contents[indx].get(), indx);
}

void Boards_ui::slotRemoveBoard(std::size_t indx)
{
    for (auto i : boards)
    {
        delete i;
    }
    boards.clear();

    delete(lout);
    lout = new QGridLayout();
    row = column = 0;

    remove_board(contents, indx);

    QWidget* widget;
    for (std::size_t i = 0; i < contents.size(); i++)
    {
        widget = create_board_ui(i, contents[i]->get_label());
        lout->addWidget(widget, row, column++);
        boards.emplace_back(widget);

        if (column == 3)
        {
            column = 0;
            row++;
        }
     }

     widget = Widget_Board::create_ADD_widget(this);
     lout->addWidget(widget, row, column++);
     boards.emplace_back(widget);

     if (column == 3)
     {
        column = 0;
        row++;
     }

     this->setLayout(lout);
}
















