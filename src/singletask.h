//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Name        : single_task.h
// Description : Task description
//               (Also used to keep track of total time spent on the activity)
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef SINGLETASK_H
#define SINGLETASK_H

#include <QObject>
#include <QString>

class SingleTask : public QObject
{
    Q_OBJECT

public:
    SingleTask(QString id, QString title);

    // Getters
    QString GetId() { return this->_id; };
    QString GetTitle() { return this->_title; };    
    unsigned int GetStatisticDailySpentTime() { return this->_daily_spent_time; };

public slots:
    void UpdateStatisticDailySpentTime(unsigned int add_time);

private:
    QString         _id;
    QString         _title;
    unsigned int    _daily_spent_time;  // Unit: minutes
};

#endif // SINGLETASK_H
