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
#include <QCloseEvent>
#include <QDebug>
#include "global.h"
#include "highlight.h"
#include "screen_unlock.h"

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
    void AutoSave();
    void UpdateRecords();
    void UpdateGUILockscreen(bool active);

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent* key_event) override;

private:
    Ui::DashBoard*  ui;
    QTimer          _timer_autosave;
    QTimer          _timer_recording_task;
    Highlight*      _ptr_highlight_manager;
    ScreenUnlock*   _ptr_screen_unlock_manager;
    QString         _recording_task;

    void toggleStatus(void);
    void recordTask(void);
    void openFile(const QString file_path);
    void saveFile(const QString file_path);
};
#endif // DASHBOARD_H
