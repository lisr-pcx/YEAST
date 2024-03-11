//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Name        : db_manager.h
// Description : Database manager (SQL Lite)
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVector>

class DbManager
{
public:

    typedef struct
    {
        unsigned int id;
        QString date;
        QString task;
        unsigned int duration;
        QString comment;
    } record_t;

    const QString       k_database_filename = "YEAST.db";

    static DbManager* GetInstance();

    QVector<record_t>   QueryGetLastRecords(unsigned int last_n_elements);
    QVector<record_t>   QueryGetRecordsOnDate(QString date);
    QVector<record_t>   QueryGetRecordsToday();
    bool                QueryInsertRecord(QString date, QString task, unsigned int duration, QString comment);

protected:

    DbManager();
    ~DbManager();

private:
    static DbManager*   _ptr_instance;
    QSqlDatabase        _database;

    bool QueryCreateRecordTable();
    void LoadFakeData(); // only for test purpose
};

#endif // DBMANAGER_H
