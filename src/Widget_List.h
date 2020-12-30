#ifndef WIDGET_LIST_H
#define WIDGET_LIST_H

#include <QtWidgets>

#include "Component.h"
#include "Widget_Card.h"

class WList;

class Widget_List : public QWidget
{
    Q_OBJECT

public:
    Widget_List(Component* list, std::size_t i, WList* p = nullptr);
    std::vector<Component*> cards();

signals:
    void signalChanged();
    void signalRemoveList(std::size_t indx);

public slots:
    void slotLabelChanged();
    void slotAddCard();
    void slotRemoveCard(std::size_t);
    void slotRemoveThisList();

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

private:
    QWidget* buttons;
    QLabel* name;
    Component* comp;
    std::size_t indx;
    WList* parent;

    QWidget* createButtons();
    QLabel* createLabel();
};

class WCard : public QWidget
{
    Q_OBJECT

public:
    explicit WCard(Component* c, std::size_t i, Widget_List* parent, QWidget* wp = nullptr);

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent* event) override
    {
        emit pressed();
    }

signals:
    void signalRemoveCard(std::size_t);
    void pressed();

public slots:
    void slotRemoveCard();
    void slotEditCard();
    void slotPressed();
    void slotShowCard(Card*);

private:
    QWidget* createButtons();
    QLabel* createLabel();

    std::size_t indx;
    Component* card;
    QWidget* buttons;
    QLabel* name;
    Widget_List* parent;
    Widget_Card* cardWidget;
    QWidget* cd;
};

#endif // WIDGET_LIST_H
