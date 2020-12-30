#include "Widget_Board.h"
#include "AddBoard.h"
#include "Boards_ui.h"

#include <QPalette>
#include <QtWidgets>
#include <QAbstractButton>
#include <QInputDialog>

Widget_Board::Widget_Board(std::size_t i, const std::string& lbl, Boards_ui* parent)
    : QWidget(parent),
      buttons(create_buttons()),
      indx(i),
      label(lbl)
{
    setAutoFillBackground(true);
    QPalette pall;
    pall.setColor(this->backgroundRole() , Qt::blue);
    this->setPalette(pall);

    QVBoxLayout* qvbxl = new QVBoxLayout();

    name = create_label();

    setMaximumSize(150, 150);
    setMouseTracking(true);

    qvbxl->addWidget(buttons);
    qvbxl->addWidget(name, 1);
    qvbxl->setSpacing(0);
    qvbxl->setContentsMargins(0, 0, 0, 0);

    this->setLayout(qvbxl);

    connect(this, SIGNAL(signalLabelChanged(std::size_t, const std::string&)),
            parent, SLOT(slotEditBoard(std::size_t, const std::string&)));

    connect(this, SIGNAL(signalRemoveBoard(std::size_t)), parent, SLOT(slotRemoveBoard(std::size_t)));

    connect(this, SIGNAL(signalPressed(std::size_t)), parent, SLOT(slotPressed(std::size_t)));
}

QLabel* Widget_Board::create_label()
{
    QLabel* name = new QLabel(QString::fromUtf8(label.data(), label.size()));
    name->setAlignment(Qt::AlignCenter);
    QFont font = name->font();
    font.setPixelSize(30);
    name->setFont(font);
    name->setStyleSheet(QStringLiteral("color: white"));

    return name;
}

void Widget_Board::enterEvent(QEvent *event)
{
    QPalette pall;
    pall.setColor(this->backgroundRole() , QColor(65, 105, 225));
    this->setPalette(pall);
    buttons->show();
}

void Widget_Board::leaveEvent(QEvent *event)
{
    QPalette pall;
    pall.setColor(this->backgroundRole() , Qt::blue);
    this->setPalette(pall);
    buttons->hide();
}

QWidget* Widget_Board::create_buttons()
{
    QHBoxLayout* hl = new QHBoxLayout;

    buttons = new QWidget(this);
    QPushButton* removeButton = new QPushButton("remove", buttons);
    QPushButton* editButton = new QPushButton("edit", buttons);

    QPixmap edit_pix(":/images/edit2.png");
    editButton->setIcon(edit_pix);
    editButton->setIconSize(QSize(20, 20));

    QPixmap remove_pix(":/images/remove.jfif");
    removeButton ->setIcon(remove_pix);
    removeButton->setIconSize(QSize(20, 20));

    connect(editButton, SIGNAL(clicked()), this, SLOT(slotLabelChanged()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveBoard()));

    hl->addWidget(removeButton);
    hl->addWidget(editButton);
    hl->setSpacing(0);
    hl->setContentsMargins(0, 0, 0, 0);
    buttons->setLayout(hl);
    buttons->hide();

    return buttons;
}

void Widget_Board::slotLabelChanged()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter board name:", QLineEdit::Normal, "Board", &bOk);

    if (bOk)
    {
       label = str.toStdString();
       name->setText(str);
       emit signalLabelChanged(indx, label);
    }
}

void Widget_Board::slotRemoveBoard()
{
    emit signalRemoveBoard(indx);
}

QWidget* Widget_Board::create_ADD_widget(Boards_ui* parent /* = nullptr */)
{
   return new AddBoard(parent);
}

Widget_Board::~Widget_Board()
{
    if (buttons)
    {
        delete buttons;
    }
}


