#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include "Widget_Checklist.h"

class CheckButton : public QCheckBox
{
    Q_OBJECT

public:
    explicit CheckButton(const std::string& text, bool isChecked, std::size_t i, Widget_Checklist* p = nullptr)
        : QCheckBox(QString::fromUtf8(text.data(), text.size()), p),
          parent(p),
          indx(i)
    {
        setChecked(isChecked);
        connect(this, SIGNAL(clicked()), this, SLOT(slotTriggered()));
        connect(this, SIGNAL(signalWasChecked(std::size_t, bool)), parent, SLOT(slotButtonChecked(std::size_t, bool)));
    }

signals:
    void signalWasChecked(std::size_t, bool);

public slots:
    void slotTriggered()
    {
        emit signalWasChecked(indx, isChecked());
    }

private:
    Widget_Checklist* parent;
    std::size_t indx;
};

#endif // CHECKBUTTON_H
