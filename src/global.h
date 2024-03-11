//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Name        : global.h
// Description : types, constants, ... shared between modules
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QVector>

// Custom types

typedef struct
{
    long app_from_left;
    long app_from_top;
    long app_width;
    long app_height;
    long history_from_left;
    long history_from_top;
    long history_width;
    long history_height;
} configuration_t;

typedef struct
{
    QString             task_title;
    unsigned int        total_duration_minutes;
} gui_task_t;

typedef struct
{
    QVector<gui_task_t> task;
    int                 current_task_index;
    unsigned int        total_duration_minutes;
} gui_information_t;

// Parameters

const QString       k_configuration_filename    = "YEAST.ini";
const QString       k_unsync_records_filename   = "unsync_records.csv";
const int           k_punch_period_ms           = 60*1000; // minutes granularity
const unsigned int  k_max_daily_hours           = 8; // max daily working hours allowed

const configuration_t   k_default_configuration = { 100, 100, 520, 520, 10, 260, 500, 250 };

// Styles for GUI

const QString k_style_for_central_widget = "background-image : url(:/image/meta/bread_off.png); "
                                           "background-repeat : no-repeat; "
                                           "background-position : center; "
                                           "opacity : 0.1; "
                                           "font-family : 'Lucida Console';";

const QString k_style_for_central_widget_monitor_active = "background-image:url(:/image/meta/bread_on.png); "
                                                          "background-repeat: no-repeat; "
                                                          "background-position: center; "
                                                          "opacity: 0.1; ";

const QString k_style_for_task_unselected = "QLabel { background-color : transparent; "
                                            "         color            : black; "
                                            "         font-weight      : normal; "
                                            "         font-size        : 12px; "
                                            "         font-family      : 'Lucida Console'; }";

const QString k_style_for_task_selected = "QLabel { background-color : transparent;"
                                          "         color            : black;"
                                          "         font-weight      : bold;"
                                          "         font-size        : 12px; "
                                          "         font-family      : 'Lucida Console'; }";

const QString k_style_for_history_widget = "QWidget { background-color : #D3D3D3;"
                                           "          border : 0 solid #000000;"
                                           "          color : black; }";

const QString k_style_for_history_table = "QTableWidget { background-color : #D3D3D3;"
                                          "               border : 1 solid #D3D3D3;"
                                          "               color : black; }"
                                          "QHeaderView::section { background-color: #D3D3D3; "
                                          "                       color : black; }";

#endif // GLOBAL_H
