//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Name        : timetracker_manager.h
// Description : Main class in charge of
//                  * load configuration
//                  * user input
//                  * record management
//                  * database load/store records
//                  * show/hide history
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef TIMETRACKER_MANAGER_H
#define TIMETRACKER_MANAGER_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QDebug>
#include "global.h"
#include "singletask.h"
#include "single_record.h"
#include "db_manager.h"

class TimeTracker : public QObject
{
    Q_OBJECT

public:
    TimeTracker(QWidget* parent = nullptr);
    ~TimeTracker();

    configuration_t     GetConfiguration() { return _configuration; };
    int                 GetNumberOfTask() { return _task_list.size(); };
    gui_information_t   GetInfoForGUI();

    void ToggleOnTask(unsigned int task_index);

signals:
    void UpdateStatus(bool monitoring, unsigned int task_index);
    void UpdateGUI(gui_information_t info);

public slots:
    void UpdateDailyTaskTime(QString task_id, unsigned int add_minutes);

private:
    QWidget*                _ptr_parent;
    configuration_t         _configuration;
    QVector<SingleTask*>    _task_list;
    SingleRecord*           _ptr_current_record;

    void LoadConfiguration();
    void LoadDailyRecords();
    void StoreRecord(SingleRecord* ptr_record);
    void LoadDataFromCSV();
    void StoreDataIntoCSV();
};

#endif // TIMETRACKER_MANAGER_H
