#include "Widget_Checklist.h"
#include "CheckButton.h"
#include "Widget_Card.h"

Widget_Checklist::Widget_Checklist(Checklist* c, std::size_t i, Widget_Card* p /* = nullptr */)
    : QWidget(p),
      parent(p),
      cl(c),
      indx(i)
{
    QVBoxLayout* vl = new QVBoxLayout();

    vl->addWidget(createTopWidget(), 1);

    for (std::size_t i = 0; i < cl->size(); i++)
    {
        CheckButton* button = new CheckButton(cl->get_task(i), cl->is_checked(i), i, this);
        buttons.emplace_back(button);
        vl->addWidget(button, 1, Qt::AlignTop);
    }

    connect(this, SIGNAL(signalRemoveChecklist(std::size_t)), parent, SLOT(slotRemoveComponent(std::size_t)));

    setLayout(vl);
}

QWidget* Widget_Checklist::createTopWidget()
{
    QWidget* top = new QWidget(this);
    QHBoxLayout* topLayout = new QHBoxLayout;

    name = new QLabel(QString::fromUtf8(cl->get_label().data(), cl->get_label().size()), this);
    QFont font = name->font();
    font.setPixelSize(16);
    name->setFont(font);
    name->setStyleSheet(QStringLiteral("color: blue"));

    QPushButton* removeButton = new QPushButton("remove checklist", top);
    QPushButton* editButton = new QPushButton("edit checklist", top);
    QPushButton* addButton = new QPushButton("add check box", top);

    removeButton->setStyleSheet("background-color: white; border: 2px solid blue");
    editButton->setStyleSheet("background-color: white; border: 2px solid blue");
    addButton->setStyleSheet("background-color: white; border: 2px solid blue");

    topLayout->addWidget(name);
    topLayout->addWidget(removeButton);
    topLayout->addWidget(editButton);
    topLayout->addWidget(addButton);

    connect(editButton, SIGNAL(clicked()), this, SLOT(slotEdit()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemove()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(slotAdd()));

    top->setLayout(topLayout);

    return top;
}

void Widget_Checklist::slotButtonChecked(std::size_t indx, bool value)
{
    cl->set_result(indx, value);
}

void Widget_Checklist::slotAdd()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter check box label:", QLineEdit::Normal, "task", &bOk);

    if (bOk)
    {
        cl->add(str.toStdString());
        buttons.emplace_back(new CheckButton(cl->get_task(cl->size() - 1), cl->is_checked(cl->size() - 1), cl->size() - 1, this));
        layout()->addWidget(buttons.back());
    }
}

void Widget_Checklist::slotRemove()
{
    emit signalRemoveChecklist(indx);
}

void Widget_Checklist::slotEdit()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter checklist label:", QLineEdit::Normal, "checklist", &bOk);

    if (bOk)
    {
        cl->set_label(str.toStdString());
        name->setText(str);
    }
}


















