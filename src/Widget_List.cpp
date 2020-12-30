#include "Widget_List.h"
#include "Widget_Board.h"
#include "AddCard.h"
#include "WList.h"

Widget_List::Widget_List(Component* list, std::size_t i, WList* p /* = nullptr*/)
    : QWidget(p),
      indx(i),
      buttons(createButtons()),
      comp(list),    
      parent(p)
{   
    setAutoFillBackground(true);
    QPalette pall;
    pall.setColor(this->backgroundRole() , Qt::white);
    this->setPalette(pall);
    setStyleSheet("border: 2px solid blue");

    QVBoxLayout* qvbxl = new QVBoxLayout();

    name = createLabel();

    setMaximumWidth(200);
    setMinimumHeight(70);
    setMouseTracking(true);

    qvbxl->addWidget(buttons);
    qvbxl->addWidget(name, 1);
    qvbxl->setSpacing(0);
    qvbxl->setContentsMargins(0, 0, 0, 0);

    this->setLayout(qvbxl);

    connect(this, SIGNAL(signalRemoveList(std::size_t)), parent, SLOT(slotRemoveList(std::size_t)));
    connect(this, SIGNAL(signalChanged()), parent, SLOT(slotListChanged()));
}

QLabel* Widget_List::createLabel()
{
    QLabel* name = new QLabel(QString::fromUtf8(comp->get_label().data(), comp->get_label().size()));
    name->setAlignment(Qt::AlignCenter);
    QFont font = name->font();
    font.setPixelSize(22);
    name->setFont(font);
    name->setStyleSheet(QStringLiteral("color: blue"));

    return name;
}

void Widget_List::enterEvent(QEvent *event)
{
    buttons->show();
}

void Widget_List::leaveEvent(QEvent *event)
{
    buttons->hide();
}

QWidget* Widget_List::createButtons()
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
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveThisList()));

    hl->addWidget(removeButton);
    hl->addWidget(editButton);
    hl->setSpacing(0);
    hl->setContentsMargins(0, 0, 0, 0);
    buttons->setLayout(hl);
    buttons->hide();

    return buttons;
}

void Widget_List::slotLabelChanged()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter list name:", QLineEdit::Normal, "List", &bOk);

    if (bOk)
    {
        const std::string list_name = str.toStdString();
        comp->set_label(list_name);
        name->setText(str);
    }
}

void Widget_List::slotAddCard()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter card name:", QLineEdit::Normal, "Card", &bOk);

    if (bOk)
    {
        const std::string card_name = str.toStdString();
        comp->add_component(card_name, "data/" + comp->get_label() + "_" + card_name + ".txt", File::create);
        emit signalChanged();
    }
}

void Widget_List::slotRemoveCard(std::size_t indx)
{
    comp->remove_component(indx);
    emit signalChanged();
}

void Widget_List::slotRemoveThisList()
{
    emit signalRemoveList(indx);
}

 std::vector<Component*> Widget_List::cards()
 {
     std::vector<Component*> cards;

     Component* card;
     for (int i = 0; (card = comp->get_child(i).get()) != nullptr; i++)
     {
         cards.emplace_back(card);
     }

     return cards;
 }

WCard::WCard(Component* c, std::size_t i, Widget_List* p, QWidget* wp /* = nullptr*/)
    : QWidget(wp),
      parent(p),
      buttons(createButtons()),
      card(c),
      indx(i)
{
    setAutoFillBackground(true);
    QPalette pall;
    pall.setColor(this->backgroundRole() , Qt::white);
    this->setPalette(pall);

    QVBoxLayout* qvbxl = new QVBoxLayout();

    name = createLabel();

    setMaximumWidth(200);
    setMinimumHeight(70);
    setMouseTracking(true);

    qvbxl->addWidget(buttons);
    qvbxl->addWidget(name, 1);
    qvbxl->setSpacing(0);
    qvbxl->setContentsMargins(0, 0, 0, 0);
    setStyleSheet("border: 2px solid blue");

    connect(this, SIGNAL(signalRemoveCard(std::size_t)), parent, SLOT(slotRemoveCard(std::size_t)));
    connect(this, SIGNAL(pressed()), this, SLOT(slotPressed()));
    this->setLayout(qvbxl);
}

QWidget* WCard::createButtons()
{
    QHBoxLayout* hl = new QHBoxLayout;

    buttons = new QWidget(this);
    QPushButton* removeButton = new QPushButton("remove", buttons);
    QPushButton* editButton = new QPushButton("edit", buttons);
    removeButton->setStyleSheet("background-color: white");
    editButton->setStyleSheet("background-color: white");

    QPixmap edit_pix(":/images/edit2.png");
    editButton->setIcon(edit_pix);
    editButton->setIconSize(QSize(20, 20));

    QPixmap remove_pix(":/images/remove.jfif");
    removeButton ->setIcon(remove_pix);
    removeButton->setIconSize(QSize(20, 20));

    connect(editButton, SIGNAL(clicked()), this, SLOT(slotEditCard()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveCard()));

    hl->addWidget(removeButton);
    hl->addWidget(editButton);
    hl->setSpacing(0);
    hl->setContentsMargins(0, 0, 0, 0);
    buttons->setLayout(hl);
    buttons->hide();

    return buttons;
}

QLabel* WCard::createLabel()
{
    QLabel* name = new QLabel(QString::fromUtf8(card->get_label().data(), card->get_label().size()));
    name->setAlignment(Qt::AlignCenter);
    QFont font = name->font();
    font.setPixelSize(18);
    name->setFont(font);
    name->setStyleSheet(QStringLiteral("color: blue"));

    return name;
}

void WCard::enterEvent(QEvent *event)
{
    buttons->show();
    QPalette pall;
    pall.setColor(this->backgroundRole() , QColor(65, 105, 225));
    this->setPalette(pall);
}

void WCard::leaveEvent(QEvent *event)
{
    buttons->hide();
    QPalette pall;
    pall.setColor(this->backgroundRole() , Qt::blue);
    this->setPalette(pall);
}

void WCard::slotEditCard()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter card name:", QLineEdit::Normal, "Card", &bOk);

    if (bOk)
    {
        card->set_label(str.toStdString());
        name->setText(str);
    }
}

void WCard::slotRemoveCard()
{
    emit signalRemoveCard(indx);
}

void WCard::slotPressed()
{
    cd = new Widget_Card(dynamic_cast<Card*>(card), this);
    cd->setVisible(true);
}

void WCard::slotShowCard(Card* c)
{
    delete cd;
    cd = new Widget_Card(c, this);
    cd->setVisible(true);
}



























