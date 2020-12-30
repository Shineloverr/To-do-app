#pragma once

#include "Leaf.h"

#include <QObject>
#include <QDateTime>
#include <QTimer>

class Reminder : public QObject, public Leaf
{
    Q_OBJECT

public:
    friend class Leaf_undo;

    Reminder(const std::string& l, const File& f, Composite* p, QObject* parent = nullptr);

    void write_to_file(File* file) const override;

    void load_from_file() override;

    void set_data(const QDateTime& dt);

    QDateTime get_dtime() const;

public slots:
    void slotTimerTimeout();

private:
    bool check_time();
    QDateTime dtime;
};
