#include "WBoard.h"
#include "WList.h"

WBoard::WBoard(Component* brd, MainWindow* p)
    : QWidget(p),
    board(brd),
    parent(p)
{
    QVBoxLayout* vlout = new QVBoxLayout;

    QWidget* top = new QWidget(this);
    QHBoxLayout* topLayout = new QHBoxLayout();

    topLayout->setContentsMargins(5, 5, 5, 0);
    //topLayout->setSpacing(0);

    addButton = new QPushButton("add list", this);
    QPixmap remove_pix(":/images/plus6.png");
    addButton ->setIcon(remove_pix);
    addButton->setIconSize(QSize(40, 40));
    addButton->setStyleSheet("background-color: white; border: 2px solid blue");

    topLayout->addWidget(label(), 0, Qt::AlignCenter);
    topLayout->addWidget(addButton, 1, Qt::AlignLeft);

    top->setLayout(topLayout);

    QWidget* containerList = new QWidget(this);
    QHBoxLayout* hlout = new QHBoxLayout();

    std::shared_ptr<Component> list;
    WList* wList;
    for (std::size_t i = 0; (list = board->get_child(i)) != nullptr; i++)
    {    
       wList = new WList(list.get(), i, this, containerList);
       hlout->addWidget(wList, 1, Qt::AlignTop);
    }

    containerList->setLayout(hlout);
    vlout->addWidget(top);
    vlout->addWidget(containerList, 1);

    /*vlout->setSpacing(0);*/
    //vlout->setContentsMargins(5, 5, 5, 0);

    connect(addButton, SIGNAL(clicked()), this, SLOT(slotAddList()));
    connect(this, SIGNAL(signalChanged(Component*)), parent, SLOT(slotBoardChanged(Component*)));

    setLayout(vlout);
}

QLabel* WBoard::label()
{
    QLabel* name = new QLabel(QString::fromUtf8(board->get_label().data(), board->get_label().size()), this);
    name->setAlignment(Qt::AlignCenter);
    QFont font = name->font();
    font.setPixelSize(40);
    name->setFont(font);
    name->setStyleSheet(QStringLiteral("color: blue"));

    name->setAutoFillBackground(true);
    QPalette pall;
    pall.setColor(name->backgroundRole() , Qt::white);
    name->setPalette(pall);

    return name;
}

void WBoard::slotAddList()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter list name:", QLineEdit::Normal, "List", &bOk);

    if (bOk)
    {
        const std::string list_name = str.toStdString();
        board->add_component(list_name, "data/" + board->get_label() + "_" + list_name + ".txt", File::create);
        emit signalChanged(board);
    }
}

void WBoard::slotRemoveList(std::size_t indx)
{
    board->remove_component(indx);
    emit signalChanged(board);
}

void WBoard::slotListChanged()
{
    emit signalChanged(board);
}












