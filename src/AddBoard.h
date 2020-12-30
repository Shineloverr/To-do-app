#ifndef ADDBOARD_H
#define ADDBOARD_H

#include <QtWidgets>

#include "Boards_ui.h"

class AddBoard : public QWidget
{
    Q_OBJECT

public:
    explicit AddBoard(Boards_ui* parent = nullptr)
        : QWidget(parent),
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

        setMaximumSize(150, 150);
        setMouseTracking(true);

        qvbxl->addWidget(name, 1);
        qvbxl->setSpacing(0);
        qvbxl->setContentsMargins(0, 0, 0, 0);

        this->setLayout(qvbxl);

        connect(this, SIGNAL(pressed()), p, SLOT(slotAddBoard()));
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
    Boards_ui* p;
};

#endif // ADDBOARD_H
