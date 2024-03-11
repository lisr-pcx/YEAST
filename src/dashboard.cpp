//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include <QMessageBox>
#include "dashboard.h"
#include "ui_dashboard.h"

DashBoard::DashBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashBoard)
{
    ui->setupUi(this);
    this->setWindowTitle("YE.A.S.T. v" +
                         QString::number(VERSION_MAJOR) + "." +
                         QString::number(VERSION_MINOR) );

    _ptr_timetracker_manager = new TimeTracker(this);
    _ptr_screen_unlock_manager = new ScreenUnlock();
    _ptr_history = nullptr;

    connect(_ptr_timetracker_manager, SIGNAL(UpdateStatus(bool, unsigned int)), this, SLOT(UpdateGUIBackground(bool, unsigned int)));
    connect(_ptr_timetracker_manager, SIGNAL(UpdateGUI(gui_information_t)), this, SLOT(UpdateGUI(gui_information_t)));
    connect(_ptr_screen_unlock_manager, SIGNAL(UpdateStatus(bool)), this, SLOT(UpdateGUILockscreen(bool)));

    // Block size
    this->setFixedSize(_ptr_timetracker_manager->GetConfiguration().app_width,
                       _ptr_timetracker_manager->GetConfiguration().app_height);
    // Place
    this->move(_ptr_timetracker_manager->GetConfiguration().app_from_left,
               _ptr_timetracker_manager->GetConfiguration().app_from_top);

    this->centralWidget()->setStyleSheet(k_style_for_central_widget);
    this->setWindowOpacity(0.85);
    this->setAttribute(Qt::WA_TranslucentBackground, false);

    // Block resize and maximize
    this->setWindowFlags( Qt::Window | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint );

    // FIXME everything below, this is just debugging
    gui_information_t data = _ptr_timetracker_manager->GetInfoForGUI();
    for (int t=0; t<_ptr_timetracker_manager->GetNumberOfTask(); t++)
    {
        QLabel* info = new QLabel(this);
        info->setStyleSheet(k_style_for_task_unselected);
        info->setGeometry(5, 10+(t*20), 500, 18);
        info->setAlignment(Qt::AlignLeft);
        QString task_title_formatted = data.task.at(t).task_title;
        task_title_formatted.resize(20, ' ');
        info->setText(QString::number(t) +
                      " : " +
                      task_title_formatted +
                      " : " +
                      QString::number(data.task.at(t).total_duration_minutes/60) +
                      "h " +
                      QString::number(data.task.at(t).total_duration_minutes%60) +
                      "m");
        info->show();
        _gui_task_info.push_back(info);
    }
}

DashBoard::~DashBoard()
{
    delete _ptr_screen_unlock_manager;
    delete _ptr_timetracker_manager;
    delete ui;
}

void DashBoard::UpdateGUIBackground(bool status, unsigned int task_index)
{
    for (auto& t : _gui_task_info)
    {
        t->setStyleSheet(k_style_for_task_unselected);
    }
    if (status == true)
    {
        this->centralWidget()->setStyleSheet(k_style_for_central_widget_monitor_active);
        _gui_task_info.at(task_index)->setStyleSheet(k_style_for_task_selected);
    }
    else
    {
        this->centralWidget()->setStyleSheet(k_style_for_central_widget);
    }

}

void DashBoard::UpdateGUI(gui_information_t info)
{
    // FIXME everything below, this is just debugging
    for (int t=0; t < info.task.size(); t++)
    {
        if (t < _gui_task_info.size())
        {
            QString task_title_formatted = info.task.at(t).task_title;
            task_title_formatted.resize(20, ' ');
            _gui_task_info.at(t)->setText(QString::number(t) +
                                          " : " +
                                          task_title_formatted +
                                          " : " +
                                          QString::number(info.task.at(t).total_duration_minutes/60) +
                                          "h " +
                                          QString::number(info.task.at(t).total_duration_minutes%60) +
                                          "m");
        }
    }
    if (info.total_duration_minutes > (k_max_daily_hours*60))
    {
        this->centralWidget()->setStyleSheet("background-color: red; ");
    }
}

void DashBoard::UpdateGUILockscreen(bool active)
{
    QString screen_lock_status_desc = "";
    if (active == true)
    {
        screen_lock_status_desc = "   [screenlock is DISABLED]";
    }
    this->setWindowTitle("YE.A.S.T. v" +
                         QString::number(VERSION_MAJOR) + "." +
                         QString::number(VERSION_MINOR) + screen_lock_status_desc);
}

void DashBoard::keyPressEvent(QKeyEvent* key_event)
{
    // Only key with CTRL are a valid command
    if (key_event->modifiers() == Qt::ControlModifier)
    {
        if (key_event->key() == Qt::Key_I)
        {
            // <CTRL> + <h> for help and information (the about page)
            // <CTRL> + <i> for help and information (the about page)

            QString description = tr("<code>YEt Another Small Timetracker<br>"
                                     "version 0.1<br>"
                                     "(2023)<br><br><br>"
                                     "</code>");

            QMessageBox::about(this, tr("YEAST"), description + "<code>"
                                                                "CTRL+I ........... show info<br>" +
                                                                "CTRL+H ........... show/hide history<br>" +
                                                                "CTRL+L ........... enable or disable auto screen unlock<br>" +
                                                                "CTRL+number ...... set corresponding task" +
                                                                "</code>");
        }
        else if (key_event->key() == Qt::Key_H)
        {
            if (_ptr_history != nullptr)
            {
                delete _ptr_history;
                _ptr_history = nullptr;
            }
            else
            {
                _ptr_history = new History(this, _ptr_timetracker_manager->GetConfiguration());
                _ptr_history->show();
            }
        }
        else if (key_event->key() == Qt::Key_Up)
        {
            // Go to previous day on history
            if (_ptr_history != nullptr)
            {
                _ptr_history->PreviousDay();
            }
        }
        else if (key_event->key() == Qt::Key_Down)
        {
            // Go to next day on history
            if (_ptr_history != nullptr)
            {
                _ptr_history->NextDay();
            }
        }
        else if ((key_event->key() == Qt::Key_L))
        {
            _ptr_screen_unlock_manager->ToggleActivation();
        }
        else
        {
            if ( (key_event->key() >= Qt::Key_0) &&
                 (key_event->key() <= Qt::Key_9) )
            {
                // <CTRL> + <single number> to set the current task
                // please note: keys are mapped into 0..9 range
                _ptr_timetracker_manager->ToggleOnTask(key_event->key() - Qt::Key_0);
            }
        }
    }
}
