#ifndef WIDGET_CHECKLIST_H
#define WIDGET_CHECKLIST_H

#include "Checklist.h"

#include <vector>
#include <QtWidgets>

class Widget_Card;

class CheckButton;

class Widget_Checklist : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Checklist(Checklist* c, std::size_t i, Widget_Card* parent = nullptr);

signals:
    void signalRemoveChecklist(std::size_t i);

public slots:
   void slotButtonChecked(std::size_t indx, bool value);
   void slotRemove();
   void slotEdit();

   void slotAdd();

private:    
    QWidget* createTopWidget();

    std::vector<CheckButton*> buttons;
    Widget_Card* parent;
    QLabel* name;
    Checklist* cl;
    std::size_t indx;
};

#endif // WIDGET_CHECKLIST_H
