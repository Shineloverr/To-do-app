#include "Widget_Reminder.h"
#include "Widget_Card.h"

Widget_Reminder::Widget_Reminder(Reminder* rem, std::size_t i, Widget_Card* p /* = nullptr */)
    : QWidget(p),
      parent(p),
      reminder(rem),
      indx(i)
{
    QVBoxLayout* vl = new QVBoxLayout;
    vl->addWidget(createTopWidget());
    vl->addWidget(createDateWidget());

    connect(this, SIGNAL(signalRemoveReminder(std::size_t)), parent, SLOT(slotRemoveComponent(std::size_t)));

    setLayout(vl);
}

QWidget* Widget_Reminder::createTopWidget()
{
    QWidget* top = new QWidget(this);
    QHBoxLayout* topLayout = new QHBoxLayout;

    name = new QLabel(QString::fromUtf8(reminder->get_label().data(), reminder->get_label().size()), this);
    QFont font = name->font();
    font.setPixelSize(16);
    name->setFont(font);
    name->setStyleSheet(QStringLiteral("color: blue"));

    QPushButton* removeButton = new QPushButton("remove reminder", top);
    QPushButton* editButton = new QPushButton("edit reminder", top);

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

void Widget_Reminder::slotEdit()
{
    bool bOk;
    QString str = QInputDialog::getText(nullptr, "Input", "Enter reminder label:", QLineEdit::Normal, "Reminder", &bOk);

    if (bOk)
    {
        reminder->set_label(str.toStdString());
        name->setText(str);
    }
}

void Widget_Reminder::slotRemove()
{
    emit signalRemoveReminder(indx);
}

QPushButton* Widget_Reminder::spinBoxMonth(QWidget* parent)
{
    const QString m[12] =
    { "September", "October", "November",
      "December", "January", "February",
      "March", "April", "May",
      "June", "July", "August" };

    std::size_t indx = reminder->get_dtime().date().month() >= 0 ? reminder->get_dtime().date().month() : 0;

    monthes = new QPushButton(m[indx], parent);

    QMenu* menu = new QMenu(monthes);

    for (std::size_t i = 0; i < 12; i++)
    {
        QAction* act = new QAction(this);
        QVariant v = qVariantFromValue(i);
        act->setData(v);
        menu->addAction(m[i], this, SLOT(slotMonthSet()));
    }

    monthes->setMenu(menu);

    return monthes;
}

QWidget* Widget_Reminder::createDateWidget()
{
    QWidget *dateWidget = new QWidget(this);

    QHBoxLayout* qhl = new QHBoxLayout;

    QWidget* yearWgt = new QWidget(dateWidget);
    QVBoxLayout* yearLout = new QVBoxLayout;
    yearLabel = new QLabel(QString::number(reminder->get_dtime().date().year()), yearWgt);
    yearLabel->setAlignment(Qt::AlignCenter);
    QPushButton* yearButton = new QPushButton("Set Year\n", yearWgt);
    connect(yearButton, SIGNAL(clicked()), this, SLOT(slotYearSet()));
    yearLout->addWidget(yearButton);
    yearLout->addWidget(yearLabel);
    yearWgt->setLayout(yearLout);

    QWidget* dayWgt = new QWidget(dateWidget);
    QVBoxLayout* dayLout = new QVBoxLayout;
    dayLabel = new QLabel(QString::number(reminder->get_dtime().date().day()), dayWgt);
    dayLabel->setAlignment(Qt::AlignCenter);
    QPushButton* dayButton = new QPushButton("Set Day\n", dayWgt);
    connect(dayButton, SIGNAL(clicked()), this, SLOT(slotDaySet()));
    dayLout->addWidget(dayButton);
    dayLout->addWidget(dayLabel);
    dayWgt->setLayout(dayLout);

    QWidget* hourWgt = new QWidget(dateWidget);
    QVBoxLayout* hourLout = new QVBoxLayout;
    hourLabel = new QLabel(QString::number(reminder->get_dtime().time().hour()), hourWgt);
    hourLabel->setAlignment(Qt::AlignCenter);
    QPushButton* hourButton = new QPushButton("Set Hour\n", hourWgt);
    connect(hourButton, SIGNAL(clicked()), this, SLOT(slotHourSet()));
    hourLout->addWidget(hourButton);
    hourLout->addWidget(hourLabel);
    hourWgt->setLayout(hourLout);

    QWidget* minueteWgt = new QWidget(dateWidget);
    QVBoxLayout* minueteLout = new QVBoxLayout;
    minueteLabel = new QLabel(QString::number(reminder->get_dtime().time().minute()), minueteWgt);
    minueteLabel->setAlignment(Qt::AlignCenter);
    QPushButton* minueteButton = new QPushButton("Set MInuete\n", minueteWgt);
    connect(minueteButton, SIGNAL(clicked()), this, SLOT(slotMinueteSet()));
    minueteLout->addWidget(minueteButton);
    minueteLout->addWidget(minueteLabel);
    minueteWgt->setLayout(minueteLout);

    qhl->addWidget(dayWgt);
    qhl->addWidget(spinBoxMonth(dateWidget));
    qhl->addWidget(yearWgt);
    qhl->addWidget(hourWgt);
    qhl->addWidget(minueteWgt);

    dateWidget->setLayout(qhl);

    return dateWidget;
}

void Widget_Reminder::slotMonthSet()
{
    QAction *act = qobject_cast<QAction*>(sender());
    std::size_t month = (std::size_t)act->data().value<std::size_t>();

    reminder->set_data(QDateTime(QDate(reminder->get_dtime().date().year(), month, reminder->get_dtime().date().day()),
                       reminder->get_dtime().time()));

    const QString m[12] =
    { "September", "October", "November",
      "December", "January", "February",
      "March", "April", "May",
      "June", "July", "August" };

    monthes->setText(m[month]);
}

void Widget_Reminder::slotYearSet()
{
    bool bOk;
    QString year = QInputDialog::getText(nullptr, "Input", "Enter year:", QLineEdit::Normal, "2019", &bOk);

    if (bOk)
    {
        if (checkYear(year))
        {
            reminder->set_data(QDateTime(QDate(std::stoi(year.toStdString()), reminder->get_dtime().date().month(),
                               reminder->get_dtime().date().day()), reminder->get_dtime().time()));
            yearLabel->setText(year);
        }
    }
}

void Widget_Reminder::slotDaySet()
{
    bool bOk;
    QString day = QInputDialog::getText(nullptr, "Input", "Enter day:", QLineEdit::Normal, "1", &bOk);

    if (bOk)
    {
        if (checkDay(day))
        {
            reminder->set_data(QDateTime(QDate(reminder->get_dtime().date().year(), reminder->get_dtime().date().month(),
                               std::stoi(day.toStdString())), reminder->get_dtime().time()));
            dayLabel->setText(day);
        }
    }
}

void Widget_Reminder::slotHourSet()
{
    bool bOk;
    QString hour = QInputDialog::getText(nullptr, "Input", "Enter hour:", QLineEdit::Normal, "7", &bOk);

    if (bOk)
    {
        if (checkHour(hour))
        {
            reminder->set_data(QDateTime(QDate(reminder->get_dtime().date()),
                               QTime(std::stoi(hour.toStdString()), reminder->get_dtime().time().minute())));
            hourLabel->setText(hour);
        }
    }
}

void Widget_Reminder::slotMinueteSet()
{
    bool bOk;
    QString min = QInputDialog::getText(nullptr, "Input", "Enter minute:", QLineEdit::Normal, "30", &bOk);

    if (bOk)
    {
        if (checkMinuete(min))
        {
            reminder->set_data(QDateTime(QDate(reminder->get_dtime().date()),
                               QTime(reminder->get_dtime().time().hour(), std::stoi(min.toStdString()))));
            minueteLabel->setText(min);
        }
    }
}

bool Widget_Reminder::checkYear(const QString& year) const
{
    if (!checkOnNumb(year) || year.size() != 4)
    {
        return false;
    }

    int y = std::stoi(year.toStdString());
    if (y < QDateTime::currentDateTime().date().year() || y > QDateTime::currentDateTime().date().year() + 2)
    {
        return false;
    }

    return true;
}
bool Widget_Reminder::checkDay(const QString& day) const
{
    if (!checkOnNumb(day) || day.size() > 2)
    {
        return false;
    }

    int d = std::stoi(day.toStdString());
    if (d < 0 || d > 31)
    {
        return false;
    }

    return true;
}
bool Widget_Reminder::checkHour(const QString& hour) const
{
    if (!checkOnNumb(hour) || hour.size() > 2)
    {
        return false;
    }

    int h = std::stoi(hour.toStdString());
    if (h < 0 || h > 24)
    {
        return false;
    }

    return true;
}
bool Widget_Reminder::checkMinuete(const QString& minuete) const
{
    if (!checkOnNumb(minuete) || minuete.size() > 2)
    {
        return false;
    }

    int m = std::stoi(minuete.toStdString());
    if (m < 0 || m > 59)
    {
        return false;
    }

    return true;
}

bool Widget_Reminder::checkOnNumb(const QString& str) const
{
    std::string s = str.toStdString();
    if (s.empty())
    {
        return false;
    }

    for (auto i : s)
    {
        if (!isdigit(i))
        {
            return false;
        }
    }

    return true;
}













