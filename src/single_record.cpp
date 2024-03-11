//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include <QDebug>
#include "single_record.h"

//SingleRecord::SingleRecord() :
//    _date{""},
//    _time_length{0},
//    _task_id{"ND"},
//    _comment{""}
//{
//    // RAII
//    QDateTime timestamp = QDateTime::currentDateTime();
//    _date = timestamp.date().toString("yyyy-MM-dd") + " " + timestamp.time().toString("hh:mm:ss");
//    connect(&_local_timer, &QTimer::timeout, this, &SingleRecord::PunchClock);
//}

SingleRecord::SingleRecord(QString id) :
    _date{""},
    _time_length{0},
    _task_id(id),
    _comment{""}
{
    // RAII
    QDateTime timestamp = QDateTime::currentDateTime();
    _date = timestamp.date().toString("yyyy-MM-dd") + " " + timestamp.time().toString("hh:mm:ss");
    connect(&_local_timer, &QTimer::timeout, this, &SingleRecord::PunchClock);
}

SingleRecord::SingleRecord(QString date,
             unsigned int time_length,
             QString task_id,
             QString comment) :
    _date(date),
    _time_length(time_length),
    _task_id(task_id),
    _comment(comment)
{
    // RAII
}

void SingleRecord::StartMonitoring()
{
    _local_timer.start(k_punch_period_ms);
}

void SingleRecord::StopMonitoring()
{
    _local_timer.stop();
}

void SingleRecord::AddMinutes(unsigned int time_minutes)
{
    _time_length += time_minutes;
}

void SingleRecord::RemoveMinutes(unsigned int time_minutes)
{
    if (_time_length >= time_minutes)
    {
        _time_length-= time_minutes;
    }
    else
    {
        _time_length = 0;
    }
}

void SingleRecord::PunchClock()
{
    AddMinutes(1);
    emit this->UpdateTaskTime(_task_id, 1);
    qDebug() << __FUNCTION__ << "Task " << _task_id << " time spent is " << _time_length;
}
