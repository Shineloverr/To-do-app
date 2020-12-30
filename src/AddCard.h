#ifndef ADDCARD_H
#define ADDCARD_H

#include <QtWidgets>
#include "Widget_List.h"

class AddCard : public QWidget
{
    Q_OBJECT

public:
    explicit AddCard(Widget_List* parent, QWidget* pw = nullptr)
        : QWidget(pw),
          p(parent)
    {
        setAutoFillBackground(true);
        QPalette pall;
        pall.setColor(this->backgroundRole() , Qt::blue);
        this->setPalette(pall);

        QVBoxLayout* qvbxl = new QVBoxLayout();

        QLabel* name = new QLabel("Add");
        name->setAlignment(Qt::AlignCenter);
        QFont font = name->font();
        font.setPixelSize(30);
        name->setFont(font);
        name->setStyleSheet(QStringLiteral("color: white"));

        setMaximumSize(200, 70);
        setMinimumHeight(70);
        setMouseTracking(true);

        qvbxl->addWidget(name, 1);
        qvbxl->setSpacing(0);
        qvbxl->setContentsMargins(0, 0, 0, 0);

        this->setLayout(qvbxl);
        //setStyleSheet("border: 2px solid white");

        connect(this, SIGNAL(pressed()), p, SLOT(slotAddCard()));
    }

signals:
    void pressed();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override
    {
        emit pressed();
    }

    virtual void enterEvent(QEvent *event) override
    {
        QPalette pall;
        pall.setColor(this->backgroundRole() , QColor(65, 105, 225));
        this->setPalette(pall);
    }

    virtual void leaveEvent(QEvent *event) override
    {
        QPalette pall;
        pall.setColor(this->backgroundRole() , Qt::blue);
        this->setPalette(pall);
    }

private:
    Widget_List* p;
};

#endif // ADDCARD_H
