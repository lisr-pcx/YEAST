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

#endif // GLOBAL_H
