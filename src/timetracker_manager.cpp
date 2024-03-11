//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include <QFile>
#include <QDir>
#include <QRegularExpression>
#include <QMessageBox>
#include <QSqlQuery>
#include "timetracker_manager.h"

TimeTracker::TimeTracker(QWidget* parent) :
    _ptr_parent(parent),
    _ptr_current_record{nullptr}
{
    // Cleanup
    _task_list.clear();

    // Load configuration from .INI file
    LoadConfiguration();

    // Load existent records (for today)
    LoadDailyRecords();
}

TimeTracker::~TimeTracker()
{
    // Stop current recording and save it
    if (_ptr_current_record != nullptr)
    {
        _ptr_current_record->StopMonitoring();
        if (_ptr_current_record->GetTimeLength() > 0)
        {
            DbManager::GetInstance()->QueryInsertRecord( _ptr_current_record->GetDate(),
                                                         _ptr_current_record->GetTaskId(),
                                                         _ptr_current_record->GetTimeLength(),
                                                         _ptr_current_record->GetComment() );
        }
        delete _ptr_current_record;
        _ptr_current_record = nullptr; // Safety (if code will be moved into a specific method)
    }

    // Final clean up, delete all objects
    for (auto& t : _task_list)
    {
        delete t;
    }
    _task_list.clear();
}

gui_information_t TimeTracker::GetInfoForGUI()
{
    gui_information_t data = {};
    data.current_task_index = -1;
    for (auto& item : _task_list)
    {
        data.task.push_back({item->GetTitle(), item->GetStatisticDailySpentTime()});
        data.total_duration_minutes += item->GetStatisticDailySpentTime();
    }
    return data;
}

void TimeTracker::ToggleOnTask(unsigned int task_index)
{
    // Triggered by user
    if ((int) task_index < _task_list.size())
    {
        if (_ptr_current_record != nullptr)
        {
            if (_task_list.at(task_index)->GetId() == _ptr_current_record->GetTaskId())
            {
                // same task
                if (_ptr_current_record->IsMonitoringActive() == true)
                {
                    _ptr_current_record->StopMonitoring();
                    emit this->UpdateStatus(false, task_index);
                    qDebug() << __FUNCTION__ << " stop for " << _ptr_current_record->GetTaskId();
                }
                else
                {
                    _ptr_current_record->StartMonitoring();
                    emit this->UpdateStatus(true, task_index);
                    qDebug() << __FUNCTION__ << " start for " << _ptr_current_record->GetTaskId();
                }
            }
            else
            {
                // task is changed, store current record and create new one
                _ptr_current_record->StopMonitoring();
                disconnect(_ptr_current_record, SIGNAL(UpdateTaskTime(QString, unsigned int)), this, SLOT(UpdateDailyTaskTime(QString, unsigned int)));
                emit this->UpdateStatus(false, task_index);
                if (_ptr_current_record->GetTimeLength() > 0)
                {
                    DbManager::GetInstance()->QueryInsertRecord( _ptr_current_record->GetDate(),
                                                                 _ptr_current_record->GetTaskId(),
                                                                 _ptr_current_record->GetTimeLength(),
                                                                 _ptr_current_record->GetComment() );
                }
                delete _ptr_current_record;
                _ptr_current_record = new SingleRecord(_task_list.at(task_index)->GetId());
                connect(_ptr_current_record, SIGNAL(UpdateTaskTime(QString, unsigned int)), this, SLOT(UpdateDailyTaskTime(QString, unsigned int)));
                _ptr_current_record->StartMonitoring();
                emit this->UpdateStatus(true, task_index);
                qDebug() << __FUNCTION__ << " new record started for " << _ptr_current_record->GetTaskId();
            }
        }
        else
        {
            // create new record and update pointers (first time)
            // task is changed
            _ptr_current_record = new SingleRecord(_task_list.at(task_index)->GetId());
            connect(_ptr_current_record, SIGNAL(UpdateTaskTime(QString, unsigned int)), this, SLOT(UpdateDailyTaskTime(QString, unsigned int)));
            _ptr_current_record->StartMonitoring();
            emit this->UpdateStatus(true, task_index);
            qDebug() << __FUNCTION__ << " new record started for " << _ptr_current_record->GetTaskId();
        }
    }
}

void TimeTracker::UpdateDailyTaskTime(QString task_id, unsigned int add_minutes)
{
    gui_information_t data = {};
    data.current_task_index = -1;
    for (auto& item : _task_list)
    {        
        if (item->GetId() == task_id)
        {
            item->UpdateStatisticDailySpentTime(add_minutes);
            qDebug() << __FUNCTION__ << " task[" << item->GetTitle() << "] total time updated: " << item->GetStatisticDailySpentTime();
            data.current_task_index = _task_list.indexOf(item);
        }
        data.task.push_back({item->GetTitle(), item->GetStatisticDailySpentTime()});
        data.total_duration_minutes += item->GetStatisticDailySpentTime();
    }

    // FIXME everything below, this is just debugging
    emit this->UpdateGUI(data);
}

void TimeTracker::LoadConfiguration()
{
    enum file_section_e { none, general, tasks };
    file_section_e section = none;

    // Default configuration
    this->_configuration = k_default_configuration;

    // List here regex to identify sections

    // re: ^\[[Gg]eneral\]$
    QRegularExpression section_general_re("^\\[[Gg]eneral\\]$");
    // re: ^\[[Gg]eneral\]$
    QRegularExpression section_tasks_re("^\\[[Tt]asks\\]$");

    // List here regex to identify single elements

    // re: ^app_width="([0-9]+)"$
    QRegularExpression app_width_re("^app_width=([0-9]+)$");
    // re: ^app_height="(.*)"$
    QRegularExpression app_height_re("^app_height=([0-9]+)$");
    // re: ^app_from_left="(.*)"$
    QRegularExpression app_from_left_re("^app_from_left=([0-9]+)$");
    // re: ^app_from_top="(.*)"$
    QRegularExpression app_from_top_re("^app_from_top=([0-9]+)$");

    // re: ^([a-zA-Z0-9_]+):([a-zA-Z0-9 ]+)$
    QRegularExpression tasks_re("^([a-zA-Z0-9_]+):([a-zA-Z0-9 ]+)$");

    QFile config_file(QDir().currentPath() + "/" + k_configuration_filename);
    if (config_file.open(QFile::ReadOnly))
    {
        QTextStream line(&config_file);
        while(!line.atEnd())
        {
            QString info = line.readLine();

            // Find the indication of the section
            if (section_general_re.match(info).hasMatch() == true)
            {
                section = general;
            }
            else if (section_tasks_re.match(info).hasMatch() == true)
            {
                section = tasks;
            }

            // Find elements inside
            switch(section)
            {
                case general:
                    if (app_width_re.match(info).hasMatch() == true)
                    {
                        this->_configuration.app_width = app_width_re.match(info).captured(1).toInt();
                        qInfo() << __FUNCTION__ << "from config file: app width " << this->_configuration.app_width;
                    }
                    if (app_height_re.match(info).hasMatch() == true)
                    {
                        this->_configuration.app_height = app_height_re.match(info).captured(1).toInt();
                        qInfo() << __FUNCTION__ << "from config file: app height " << this->_configuration.app_height;
                    }
                    if (app_from_left_re.match(info).hasMatch() == true)
                    {
                        this->_configuration.app_from_left = app_from_left_re.match(info).captured(1).toInt();
                        qInfo() << __FUNCTION__ << "from config file: app from left " << this->_configuration.app_from_left;
                    }
                    if (app_from_top_re.match(info).hasMatch() == true)
                    {
                        this->_configuration.app_from_top = app_from_top_re.match(info).captured(1).toInt();
                        qInfo() << __FUNCTION__ << "from config file: app from top " << this->_configuration.app_from_top;
                    }
                    break;
                case tasks:
                    if (tasks_re.match(info).hasMatch() == true)
                    {
                        SingleTask* new_task = new SingleTask(tasks_re.match(info).captured(1),
                                                              tasks_re.match(info).captured(2));
                        _task_list.push_back(new_task);
                        qInfo() << __FUNCTION__ << "configuration: added task " << new_task->GetId();
                    }
                    break;
                case none:
                    // break; omitted for optimization
                default:
                    // do nothing
                    break;
            }
        }
    }
    else
    {
        QMessageBox::warning(_ptr_parent, "Loading configuration", "Unable to open " + k_configuration_filename + "\nUse default configuration");
    }
    config_file.close();
}

void TimeTracker::LoadDailyRecords()
{
    QVector<DbManager::record_t> today_records = DbManager::GetInstance()->QueryGetRecordsToday();
    for (auto& elem : today_records)
    {
        // Update statistics
        UpdateDailyTaskTime(elem.task, elem.duration);
    }
}

void TimeTracker::StoreRecord(SingleRecord* ptr_record)
{
    if (DbManager::GetInstance()->QueryInsertRecord( ptr_record->GetDate(),
                                                     ptr_record->GetTaskId(),
                                                     ptr_record->GetTimeLength(),
                                                     ptr_record->GetComment() ))
    {
        qInfo() << __FUNCTION__ << " Store into DB";
    }
    else
    {
        qInfo() << __FUNCTION__ << " Error when storing data into DB, saved temporarly in: " << k_unsync_records_filename;
        QFile unsync_records_file(QDate::currentDate().toString("yyyy_MM_dd") + "_" + k_unsync_records_filename);
        if (unsync_records_file.open(QFile::WriteOnly | QIODevice::Append))
        {
            QTextStream text(&unsync_records_file);
            text << "\""    << ptr_record->GetDate() <<
                    "\";\"" << ptr_record->GetTaskId() <<
                    "\";\"" << ptr_record->GetTimeLength() <<
                    "\";\"" << ptr_record->GetComment() << "\";\n";
        }
        else
        {
            qInfo() << __FUNCTION__ << " Error when writing file: " << k_unsync_records_filename;
        }
        unsync_records_file.close();
    }
}

void TimeTracker::LoadDataFromCSV()
{
    // re: ^"(.*)";"([a-zA-Z0-9_]+)";"(.*)";"(.*)";$
    QRegularExpression records_re("^\"(.*)\";\"([a-zA-Z0-9_]+)\";\"(.*)\";\"(.*)\";$");

    if (QDir("records").exists() == true)
    {
        QString filename = QDate::currentDate().toString("yyyy_MM_dd") + "_data.report";
        QFile report_file("records/" + filename);

        if (report_file.open(QFile::ReadOnly))
        {
            QTextStream line(&report_file);
            while(!line.atEnd())
            {
                QString info = line.readLine();
                if (records_re.match(info).hasMatch() == true)
                {
                    // insert pre-existent record read from file
                    SingleRecord* ptr_prev_record = new SingleRecord(records_re.match(info).captured(1),
                                                                     records_re.match(info).captured(3).toUInt(),
                                                                     records_re.match(info).captured(2),
                                                                     records_re.match(info).captured(4));

                    qInfo() << __FUNCTION__ << "import record from previous session [" << info << "]";

                    // Update statistics
                    UpdateDailyTaskTime(records_re.match(info).captured(2), records_re.match(info).captured(3).toUInt());
                }
            }
            report_file.close();
        }
    }
}

void TimeTracker::StoreDataIntoCSV()
{
    // Save all records into .report file inside folder "/records"
    if (QDir("records").exists() == false)
    {
        QDir().mkdir("records");
    }
    QString filename = QDate::currentDate().toString("yyyy_MM_dd") + "_data.report";
    QFile report_file("records/" + filename);

    if (report_file.open(QFile::WriteOnly))
    {
        QTextStream report(&report_file);
//        for (auto& record : _record_list)
//        {
//            report << "\""    << record->GetDate() <<
//                      "\";\"" << record->GetTaskId() <<
//                      "\";\"" << record->GetTimeLength() <<
//                      "\";\"" << record->GetComment() << "\";\n";
//        }
        report << "--------------\ntasks summary:\n--------------\n";
        for (auto& task : _task_list)
        {
            report << task->GetId() << " : " <<
                      task->GetStatisticDailySpentTime()/60 << "h " <<
                      task->GetStatisticDailySpentTime()%60 << "m\n";
        }
    }
    report_file.close();
}
