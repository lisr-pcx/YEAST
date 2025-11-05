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

// Parameters

const QString       k_text_filename             = "YEAST.txt";
const int           k_recording_task_period_ms  = 60*1000;
const unsigned int  k_max_daily_hours           = 8;            // max daily working hours allowed
const int           k_autosave_period_ms        = 5*60*1000;

// Styles for GUI

const QString k_style_for_central_widget = "background-image : url(:/image/meta/bread_off.png); "
                                           "background-repeat : no-repeat; "
                                           "background-position : center; ";

const QString k_style_for_central_widget_recording = "background-image:url(:/image/meta/bread_on.png); "
                                                     "background-repeat: no-repeat; "
                                                     "background-position: center; ";

static QString convMinutesToReadableString(unsigned int minutes)
{
    unsigned int hh = minutes / 60;
    unsigned int mm = minutes % 60;
    QString text = QString::number(hh) + "h";
    if (mm >= 45)
    {
        text.append("45");
    }
    else if (mm >= 30)
    {
        text.append("30");
    }
    else if (mm >= 15)
    {
        text.append("15");
    }
    // Output format is:
    // (where N is number of hours, approx to floor, granularity is 15 min)
    //      Nh
    //      Nh15
    //      Nh30
    //      Nh45
    return text;
};

#endif // GLOBAL_H
