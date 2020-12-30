#ifndef WIDGET_CARD_H
#define WIDGET_CARD_H

#include "Card.h"

#include <QtWidgets>

class WCard;

class Widget_Card : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Card(Card* c, WCard* wc, QWidget* p = nullptr);

    ~Widget_Card();

signals:
    void signalCardChanged(Card*);

public slots:
    void slotAddChecklist();
    void slotAddText();
    void slotAddReminder();
    void slotRemoveComponent(std::size_t);
    void slotUndo();

private:
    QLabel* label();
    Card* card;
    QLabel* name;
    QWidget* buttons;
    QVBoxLayout* vlout;
    std::size_t childNumber;
    WCard* parent;

    QWidget* createButtons();
};

#endif // WIDGET_CARD_H
