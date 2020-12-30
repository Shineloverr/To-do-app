#ifndef WIDGET_REMINDER_H
#define WIDGET_REMINDER_H

#include "Reminder.h"

#include <QtWidgets>

class Widget_Card;

class Widget_Reminder : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Reminder(Reminder* rem, std::size_t i, Widget_Card* p = nullptr);

signals:
    void signalRemoveReminder(std::size_t i);

public slots:
    void slotEdit();
    void slotRemove();
    void slotMonthSet();
    void slotYearSet();
    void slotDaySet();
    void slotHourSet();
    void slotMinueteSet();

private:
    QWidget* createTopWidget();
    QWidget* createDateWidget();
    QPushButton* spinBoxMonth(QWidget*);
    bool checkYear(const QString& year) const;
    bool checkDay(const QString& day) const;
    bool checkHour(const QString& hour) const;
    bool checkMinuete(const QString& minuete) const;
    bool checkOnNumb(const QString& str) const;

    Widget_Card* parent = nullptr;
    Reminder* reminder;
    std::size_t indx;
    QLabel* name;
    QLabel* yearLabel;
    QLabel* dayLabel;
    QLabel* hourLabel;
    QLabel* minueteLabel;
    QPushButton* monthes;
};

#endif // WIDGET_REMINDER_H
