#include "Widget_Card.h"
#include "Widget_Checklist.h"
#include "Widget_List.h"
#include "Widget_Text.h"
#include "Undo.h"
#include "Widget_Reminder.h"

extern Undo undo;

Widget_Card::Widget_Card(Card* c, WCard* wc, QWidget* p/*  = nullptr */)
    : QWidget(p),
      card(c),
      name(label()),
      buttons(createButtons()),
      childNumber(0),
      parent(wc)
{
    vlout = new QVBoxLayout;

    QWidget* top = new QWidget(this);

    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(5, 5, 5, 0);

    topLayout->addWidget(name, 0, Qt::AlignCenter);
    topLayout->addWidget(buttons, 1, Qt::AlignLeft);
    top->setLayout(topLayout);
    vlout->addWidget(top);

    Component* child;
    for (std::size_t i = 0; (child = card->get_child(i).get()) != nullptr; i++)
    {
        Leaf* l = dynamic_cast<Leaf*>(child);

        switch (l->get_type())
        {
            case Leaf::Text:
            vlout->addWidget(new Widget_Text(dynamic_cast<Text*>(l), i, this));
            break;

            case Leaf::Checklist:
            vlout->addWidget(new Widget_Checklist(dynamic_cast<Checklist*>(l), i, this));
            break;

            case Leaf::Reminder:
            vlout->addWidget(new Widget_Reminder(dynamic_cast<Reminder*>(l), i, this));
            break;

            default:
            break;
        }

        childNumber++;
    }

    connect(this, SIGNAL(signalCardChanged(Card*)), parent, SLOT(slotShowCard(Card*)));

    setLayout(vlout);
}

QLabel* Widget_Card::label()
{
    QLabel* label = new QLabel(QString::fromUtf8(card->get_label().data(), card->get_label().size()));
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPixelSize(30);
    label->setFont(font);
    label->setStyleSheet(QStringLiteral("color: blue"));

    return label;
}

QWidget* Widget_Card::createButtons()
{
    QWidget* wgt = new QWidget(this);
    QHBoxLayout* hl = new QHBoxLayout;

    QPushButton* add_ch = new QPushButton("add checklist", wgt);
    QPushButton* add_rem = new QPushButton("add reminder", wgt);
    QPushButton* add_text = new QPushButton("add note", wgt);
    QPushButton* undoButton = new QPushButton("undo", wgt);

    connect(add_ch, SIGNAL(clicked()), this, SLOT(slotAddChecklist()));
    connect(add_text, SIGNAL(clicked()), this, SLOT(slotAddText()));
    connect(add_rem, SIGNAL(clicked()), this, SLOT(slotAddReminder()));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(slotUndo()));

    hl->addWidget(add_ch);
    hl->addWidget(add_rem);
    hl->addWidget(add_text);
    hl->addWidget(undoButton);

    add_ch->setStyleSheet("background-color: white; border: 2px solid blue");
    add_rem->setStyleSheet("background-color: white; border: 2px solid blue");
    add_text->setStyleSheet("background-color: white; border: 2px solid blue");
    undoButton->setStyleSheet("background-color: white; border: 2px solid blue");

    wgt->setLayout(hl);

    return wgt;
}

void Widget_Card::slotAddChecklist()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter checklist label:", QLineEdit::Normal, "checklist", &bOk);

    if (bOk)
    {
        Leaf* child = card->create_child(str.toStdString(), "data/" + card->get_label() + "_" + str.toStdString() + ".txt",
                                         Leaf::Checklist, File::create);

        if (Checklist* cl = dynamic_cast<Checklist*>(child))
        {
            vlout->addWidget(new Widget_Checklist(cl, childNumber++, this));
        }
    }
}

void Widget_Card::slotAddText()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter note label:", QLineEdit::Normal, "Note", &bOk);

    if (bOk)
    {
        Leaf* child = card->create_child(str.toStdString(), "data/" + card->get_label() + "_" + str.toStdString() + ".txt",
                                         Leaf::Text, File::create);

        if (Text* t = dynamic_cast<Text*>(child))
        {
            vlout->addWidget(new Widget_Text(t, childNumber++, this));
        }
    }
}

void Widget_Card::slotAddReminder()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter reminder label:", QLineEdit::Normal, "Reminder", &bOk);

    if (bOk)
    {
        Leaf* child = card->create_child(str.toStdString(), "data/" + card->get_label() + "_" + str.toStdString() + ".txt",
                                         Leaf::Reminder, File::create);

        if (Reminder* r = dynamic_cast<Reminder*>(child))
        {
            vlout->addWidget(new Widget_Reminder(r, childNumber++, this));
        }
    }
}

void Widget_Card::slotUndo()
{
    std::cout << "Undo slot\n";
    restore();
    emit signalCardChanged(card);
}

void Widget_Card::slotRemoveComponent(std::size_t indx)
{
    card->remove_component(indx);
    emit signalCardChanged(card);
}

Widget_Card::~Widget_Card()
{
   delete buttons;
   delete name;
   delete vlout;
}















