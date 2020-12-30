#ifndef WIDGET_TEXT_H
#define WIDGET_TEXT_H

#include "Text.h"

#include <QtWidgets>
#include <QTextEdit>

class Widget_Card;

class Widget_Text : public QWidget
{
    Q_OBJECT

public:
    Widget_Text(Text* t, std::size_t i, Widget_Card* p = nullptr);

signals:
    void signalRemove(std::size_t i);

public slots:
    void slotEdit();
    void slotRemove();
    void slotTextChanged();

private:
    QWidget* createTopWidget();

    Text* text;
    QTextEdit* textEdit;
    std::size_t indx;
    QLabel* name;
    Widget_Card* parent;
};

#endif // WIDGET_TEXT_H
