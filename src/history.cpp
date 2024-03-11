//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include <QDate>
#include <QVector>
#include <QTableWidgetItem>
#include <QDebug>
#include "history.h"
#include "ui_history.h"
#include "db_manager.h"

History::History(QWidget *parent, configuration_t configuration) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    this->setFixedSize(configuration.history_width,
                       configuration.history_height);
    this->move(configuration.history_from_left,
               configuration.history_from_top);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet(k_style_for_history_widget);

    connect(ui->de_SearchDate, SIGNAL(dateChanged(const QDate&)), this, SLOT(LoadRecords(const QDate&)));

    ui->de_SearchDate->setDate(QDate::currentDate());
}

History::~History()
{
    delete ui;
}

void History::LoadRecords(const QDate& search_date)
{
    QVector<DbManager::record_t> records = DbManager::GetInstance()->QueryGetRecordsOnDate(search_date.toString("yyyy-MM-dd"));
    ui->tw_Records->clear();
    ui->tw_Records->setRowCount(records.size());
    ui->tw_Records->setColumnCount(4);
    ui->tw_Records->setHorizontalHeaderLabels({"Datetime", "Task ID", "Duration", "Comments"});
    ui->tw_Records->setStyleSheet(k_style_for_history_table);
    ui->tw_Records->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int current_row = 0;
    for (auto& elem : records)
    {
        QTableWidgetItem* tmp_item = new QTableWidgetItem(QString::number(elem.id));
        ui->tw_Records->setVerticalHeaderItem(current_row, tmp_item);
        tmp_item = new QTableWidgetItem(elem.date);
        tmp_item->setFlags(Qt::NoItemFlags);
        ui->tw_Records->setItem(current_row, 0, tmp_item);
        tmp_item = new QTableWidgetItem(elem.task);
        tmp_item->setFlags(Qt::NoItemFlags);
        ui->tw_Records->setItem(current_row, 1, tmp_item);
        tmp_item = new QTableWidgetItem(QString::number(elem.duration));
        tmp_item->setFlags(Qt::NoItemFlags);
        ui->tw_Records->setItem(current_row, 2, tmp_item);
        tmp_item = new QTableWidgetItem(elem.comment);
        tmp_item->setFlags(Qt::ItemIsEditable);
        ui->tw_Records->setItem(current_row, 3, tmp_item);
        current_row++;
        delete tmp_item;
    }
}

void History::PreviousDay()
{
    QDate new_date = ui->de_SearchDate->date().addDays(-1);
    ui->de_SearchDate->setDate(new_date);
}

void History::NextDay()
{
    QDate new_date = ui->de_SearchDate->date().addDays(+1);
    if (new_date <= QDate::currentDate())
    {
        ui->de_SearchDate->setDate(new_date);
    }
}
