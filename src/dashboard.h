//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// File        : dashboard.h
// Description : Main application window (GUI)
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QVector>
#include <QDebug>
#include "global.h"
#include "screen_unlock.h"
#include "timetracker_manager.h"
#include "history.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DashBoard; }
QT_END_NAMESPACE

class DashBoard : public QMainWindow
{
    Q_OBJECT

public:
    DashBoard(QWidget *parent = nullptr);
    ~DashBoard();

public slots:
    void UpdateGUIBackground(bool status, unsigned int task_index);
    void UpdateGUI(gui_information_t info);
    void UpdateGUILockscreen(bool active);

private:
    Ui::DashBoard*  ui;
    History*        _ptr_history;

    ScreenUnlock* _ptr_screen_unlock_manager;
    TimeTracker* _ptr_timetracker_manager;

    QVector<QLabel*> _gui_task_info;

    // Application is mainly managed via key shortcut:
    //      CTRL + 0            : start counting on task "0"
    //      ...
    //      CTRL + 9            : start counting on task "9"
    //      CTRL + <UP>         : move to previous on daily history
    //      CTRL + <DOWN>       : move to next on daily history
    //      CTRL + <RIGHT>         : add time on selected task
    //      CTRL + <LEFT>       : remove time on selected task
    //      CTRL + l/L          : enable/disable on screen unlock

    void keyPressEvent(QKeyEvent* key_event);   // override
};
#endif // DASHBOARD_H
