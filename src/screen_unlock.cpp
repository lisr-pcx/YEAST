//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================
#include "screen_unlock.h"

ScreenUnlock::ScreenUnlock()
{    
    connect(&_timer_screen_unlock, &QTimer::timeout, this, &ScreenUnlock::SendSignalsToOS);
}

ScreenUnlock::~ScreenUnlock()
{
    _timer_screen_unlock.stop();
}

void ScreenUnlock::SendSignalsToOS()
{
    SetThreadExecutionState(ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED | ES_CONTINUOUS);
}

void ScreenUnlock::ToggleActivation()
{
    if (_timer_screen_unlock.isActive() == true)
    {        
        _timer_screen_unlock.stop();
    }
    else
    {
        _timer_screen_unlock.start(k_screen_unlock_period_trigger);
    }
    emit this->UpdateStatus(_timer_screen_unlock.isActive());
}
