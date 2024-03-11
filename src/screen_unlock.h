//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Name        : screen_unlock.h
// Description : Class in charge to avoid lock screen.
//               (Done by sending periodic signals to OS)
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef SCREENUNLOCK_H
#define SCREENUNLOCK_H

#include <windows.h>
#include <QObject>
#include <QTimer>

// variables for background task to avoid screen lock by IT admin
// already defined in Qt libraries project included to this project
// #define ES_CONTINUOUS           0x80000000
// #define ES_DISPLAY_REQUIRED     0x00000002
// #define ES_SYSTEM_REQUIRED      0x00000001

class ScreenUnlock : public QObject
{    
    Q_OBJECT

public:
    const int k_screen_unlock_period_trigger = 30000;   // period to send trigger to OS, in ms

    ScreenUnlock();
    ~ScreenUnlock();

    void ToggleActivation();

signals:
    void UpdateStatus(bool active);

private slots:
    void SendSignalsToOS();

private:
    QTimer _timer_screen_unlock;
};

#endif // SCREENUNLOCK_H
