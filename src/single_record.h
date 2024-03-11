//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Name        : single_record.h
// Description : Record
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef SINGLERECORD_H
#define SINGLERECORD_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QDate>
#include <QTimer>
#include "global.h"

class SingleRecord : public QObject
{
    Q_OBJECT

public:
//    SingleRecord();
    SingleRecord(QString id);
    SingleRecord(QString date,
                 unsigned int time_length,
                 QString task_id,
                 QString comment);

    QString GetDate()            { return this->_date; };
    unsigned int GetTimeLength() { return this->_time_length; };
    QString GetTaskId()          { return this->_task_id; };
    QString GetComment()         { return this->_comment; };

    bool IsMonitoringActive()    { return this->_local_timer.isActive(); };

    void StartMonitoring();
    void StopMonitoring();
    void AddMinutes(unsigned int time_minutes);
    void RemoveMinutes(unsigned int time_minutes);
    void SetComment(QString text) { this->_comment = text; };

public slots:
    void PunchClock();

signals:
    void UpdateTaskTime(QString task_id, unsigned int add_minutes);

private:    
    QString         _date;              // date of record, in format yyyy_MM_dd
    unsigned int    _time_length;       // duration of record, in minutes
    QString         _task_id;           // task associated
    QString         _comment;           // user comments and notes
    QTimer          _local_timer;       // timer used for counting minutes
};

#endif // SINGLERECORD_H
