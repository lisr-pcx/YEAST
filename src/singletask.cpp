//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include "singletask.h"

SingleTask::SingleTask(QString id, QString title) :
    _id(id),
    _title(title),
    _daily_spent_time{0}
{
    // RAII
}

void SingleTask::UpdateStatisticDailySpentTime(unsigned int add_time)
{
    _daily_spent_time += add_time;
}
