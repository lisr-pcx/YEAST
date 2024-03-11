//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Name        : history.h
// Description : Show/navigate record history (GUI)
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include "global.h"

namespace Ui {
class History;
}

class History : public QWidget
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = nullptr, configuration_t configuration = k_default_configuration);
    ~History();

    void PreviousDay();
    void NextDay();

public slots:
    void LoadRecords(const QDate& search_date);

private:
    Ui::History *ui;
};

#endif // HISTORY_H
