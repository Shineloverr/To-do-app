#include "Widget_Text.h"
#include "Widget_Card.h"

Widget_Text::Widget_Text(Text* t, std::size_t i, Widget_Card* p /*= nullptr*/)
    : QWidget(p),
      indx(i),
      parent(p),
      text(t)
{
    QVBoxLayout* vlout = new QVBoxLayout();
    textEdit = new QTextEdit(this);

    vlout->addWidget(createTopWidget(), 1);
    vlout->addWidget(textEdit, 1);

    if (text->empty())
    {
        textEdit->setText("Edit it");
    }
    else
    {
        textEdit->setText(QString::fromUtf8(text->get_text().data(), text->get_text().size()));
    }
    textEdit->setTextColor(Qt::blue);

    connect(this, SIGNAL(signalRemove(std::size_t)), parent, SLOT(slotRemoveComponent(std::size_t)));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(slotTextChanged()));

    setLayout(vlout);
}

QWidget* Widget_Text::createTopWidget()
{
    QWidget* top = new QWidget(this);
    QHBoxLayout* topLayout = new QHBoxLayout;

    name = new QLabel(QString::fromUtf8(text->get_label().data(), text->get_label().size()), this);
    QFont font = name->font();
    font.setPixelSize(16);
    name->setFont(font);
    name->setStyleSheet(QStringLiteral("color: blue"));

    QPushButton* removeButton = new QPushButton("remove note", top);
    QPushButton* editButton = new QPushButton("edit note", top);

    removeButton->setStyleSheet("background-color: white; border: 2px solid blue");
    editButton->setStyleSheet("background-color: white; border: 2px solid blue");

    topLayout->addWidget(name);
    topLayout->addWidget(removeButton);
    topLayout->addWidget(editButton);

    connect(editButton, SIGNAL(clicked()), this, SLOT(slotEdit()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemove()));

    top->setLayout(topLayout);

    return top;
}

void Widget_Text::slotEdit()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter note label:", QLineEdit::Normal, "Note", &bOk);

    if (bOk)
    {
        text->set_label(str.toStdString());
        name->setText(str);
    }
}

void Widget_Text::slotRemove()
{
    emit signalRemove(indx);
}
\
void Widget_Text::slotTextChanged()
{
    text->set_text(textEdit->toPlainText().toStdString());
}

































