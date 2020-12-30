#include "Undo.h"
#include "SystemTray.h"

extern Undo undo;

Reminder::Reminder(const std::string& l, const File& f, Composite* p, QObject* parent /* = nullptr*/)
    : QObject(parent),
      Leaf(l, f, p, Leaf::Reminder)
{
    load_from_file();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerTimeout()));
    timer->start(59000); // invokes every 59 seconds; offset = +- minute
}

void Reminder::write_to_file(File* file) const
{
    *file << std::to_string(get_type()) << " " << get_label() << " " << get_file()->get_filename() << "\n";

    File* f = get_file();
    f->open(f->get_filename(), File::create);

    *f << std::to_string(dtime.date().day()) << " " << std::to_string(dtime.date().month())
       << " " << std::to_string(dtime.date().year());
    *f << " " << std::to_string(dtime.time().hour()) << " " << std::to_string(dtime.time().minute()) << "\n";
}

void Reminder::load_from_file()
{
    File* f = get_file();

    std::string day, month, year, hour, minute;

    if (*f >> day >> month >> year >> hour >> minute)
    {
        dtime.setDate(QDate(std::stoi(year), std::stoi(month), std::stoi(day)));
        dtime.setTime(QTime(std::stoi(hour), std::stoi(minute), 0));
    }
}

void Reminder::slotTimerTimeout()
{
    if (check_time())
    {
        SystemTray::instance()->slotShowMessage(get_label());
    }
}

void Reminder::set_data(const QDateTime& dt)
{
    undo.reminder_save(this, dtime);
    dtime = dt;
}

QDateTime Reminder::get_dtime() const
{
    return dtime;
}

bool Reminder::check_time()
{
    return QDateTime::currentDateTime().date() == dtime.date() &&
           QDateTime::currentDateTime().time().hour() == dtime.time().hour() &&
           QDateTime::currentDateTime().time().minute() == dtime.time().minute();
}












