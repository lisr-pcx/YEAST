//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include <QDebug>
#include <QDate>
#include "db_manager.h"

DbManager* DbManager::_ptr_instance = nullptr;

DbManager* DbManager::GetInstance()
{
    if (DbManager::_ptr_instance == nullptr)
    {
        DbManager::_ptr_instance = new DbManager();
    }
    return DbManager::_ptr_instance;
}

DbManager::DbManager()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName(this->k_database_filename);

    if (_database.open())
    {
        QueryCreateRecordTable();
        //LoadFakeData(); remove me!
    }
    else
    {
        qInfo() << __FUNCTION__ << " Error when connecting to database";
    }
}

bool DbManager::QueryCreateRecordTable()
{
    bool ret_value = true;
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS user_records (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                           "task_datetime TEXT, "
                                                           "task_id TEXT, "
                                                           "task_duration INTEGER, "
                                                           "task_comment TEXT)");
    if (!query.exec())
    {
        qInfo() << __FUNCTION__ << " Error, query: " << query.lastError();
        ret_value = false;
    }
    return ret_value;
}

QVector<DbManager::record_t> DbManager::QueryGetLastRecords(unsigned int last_n_elements)
{
    QVector<DbManager::record_t> result;
    QSqlQuery query;
    query.prepare("SELECT * FROM user_records ORDER BY id DESC LIMIT (:n_elements)");
    query.bindValue(":n_elements", last_n_elements);
    if (query.exec())
    {
        while (query.next())
        {
            DbManager::record_t element = { query.value(0).toUInt(),
                                            query.value(1).toString(),
                                            query.value(2).toString(),
                                            query.value(3).toUInt(),
                                            query.value(4).toString()};
            result.push_back(element);
        }
    }
    else
    {
        qInfo() << __FUNCTION__ << " Error, query: " << query.lastError();
    }
    return result;
}

QVector<DbManager::record_t> DbManager::QueryGetRecordsOnDate(QString date)
{
    QVector<DbManager::record_t> result;
    QString start_time = date + " 00:00:00";
    QString end_time = date + " 23:59:59";

    QSqlQuery query;
    query.prepare("SELECT * FROM user_records WHERE task_datetime BETWEEN :start_date AND :end_date");
    query.bindValue(":start_date", start_time);
    query.bindValue(":end_date", end_time);
    if (query.exec())
    {
        while (query.next())
        {
            DbManager::record_t element = { query.value(0).toUInt(),
                                            query.value(1).toString(),
                                            query.value(2).toString(),
                                            query.value(3).toUInt(),
                                            query.value(4).toString()};
            result.push_back(element);
        }
    }
    else
    {
        qInfo() << __FUNCTION__ << " Error, query: " << query.lastError();
    }
    return result;
}

QVector<DbManager::record_t> DbManager::QueryGetRecordsToday()
{
    QString today = QDate::currentDate().toString("yyyy-MM-dd");
    QVector<DbManager::record_t> result = QueryGetRecordsOnDate(today);
    return result;
}

bool DbManager::QueryInsertRecord(QString date, QString task, unsigned int duration, QString comment)
{
    bool ret_value = true;
    QSqlQuery query;
    query.prepare("INSERT INTO user_records (task_datetime, task_id, task_duration, task_comment) VALUES (:val0, :val1, :val2, :val3)");
    query.bindValue(":val0", date);
    query.bindValue(":val1", task);
    query.bindValue(":val2", duration);
    query.bindValue(":val3", comment);
    if (!query.exec())
    {
        qInfo() << __FUNCTION__ << " Error, query: " << query.lastError();
        ret_value = false;
    }
    return ret_value;
}

void DbManager::LoadFakeData() // only for test purpose
{
    QueryInsertRecord("2024-01-12 09:00:00", "AAAA", 10, "nn");
    QueryInsertRecord("2024-01-14 10:30:00", "AAAA", 10, "nn");
    QueryInsertRecord("2024-03-09 00:00:00", "BBBB", 50, "nn");
    QueryInsertRecord("2024-03-09 19:30:00", "BBBB", 60, "nn");
    QueryInsertRecord("2024-03-09 23:59:00", "BBBB", 70, "nn");
    QueryInsertRecord("2024-03-07 09:00:00", "CCCC", 33, "today");
    QueryInsertRecord("2024-03-13 12:00:00", "DDDD", 44, "futuro");
    QueryInsertRecord("2024-03-13 12:00:23", "DDDD", 44, "futuro");
}
