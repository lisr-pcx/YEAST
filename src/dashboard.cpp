//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include <QMessageBox>
#include <QDate>
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

    connect(&_timer_autosave, &QTimer::timeout, this, &DashBoard::AutoSave);

    _ptr_screen_unlock_manager = new ScreenUnlock();
    connect(_ptr_screen_unlock_manager, SIGNAL(UpdateStatus(bool)), this, SLOT(UpdateGUILockscreen(bool)));

    //this->centralWidget()->setStyleSheet(k_style_for_central_widget);
    //this->setWindowOpacity(0.90);
    //this->setAttribute(Qt::WA_TranslucentBackground, false);

    // block resize and maximize
    this->setWindowFlags( Qt::Window | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint );

    // setup information labels
    QFont info_font;
    info_font.setFamily("Arial");
    info_font.setPointSize(8);
    info_font.setBold(true);
    ui->lblRecording->setStyleSheet("QLabel { background-color : red; color : white; }");
    ui->lblRecording->setFont(info_font);
    ui->lblRecording->setVisible(false);
    ui->lblKeepAlive->setStyleSheet("QLabel { background-color : cyan; color : white; }");
    ui->lblKeepAlive->setFont(info_font);
    ui->lblKeepAlive->setVisible(false);

    // setup editor
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Courier);
    font.setFixedPitch(true);
    font.setPointSize(10);
    ui->txtEditor->setFont(font);
    ui->txtEditor->setTextColor(Qt::black);
    // set tab width to 4 characters
    const int tab_stop = 4;
    QFontMetrics metrics(font);
    ui->txtEditor->setTabStopWidth(tab_stop * metrics.width(' '));
    // set custom highlighting
    _ptr_highlight_manager = new Highlight(ui->txtEditor->document());

    // load text
    this->openFile(k_text_filename);

    // no task recording at startup
    this->_recording_task = "";
    connect(&_timer_recording_task, &QTimer::timeout, this, &DashBoard::UpdateRecords);


    // see https://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html
}

DashBoard::~DashBoard()
{
    delete _ptr_screen_unlock_manager;
    delete ui;
}

void DashBoard::closeEvent(QCloseEvent *event)
{
    // save the current text on exit application
    this->saveFile(k_text_filename);
}

void DashBoard::AutoSave()
{
    // periodically save the current text
    this->saveFile(k_text_filename);
}

void DashBoard::UpdateRecords()
{    
    int cursor_position = ui->txtEditor->textCursor().position();

    // WARNING: it seems works fine event when writing during the
    // time update (replace the entire text in the QTextEdit), but
    // probably it's not a good design...

    // search the the task on the text and update the time spent on it
    QString today = QDate::currentDate().toString("yyyy-MM-dd");
    QString record = "\n" + today + "\t\t([0-9]+)\t\t" + _recording_task;
    QRegularExpression re_task_on_timesheet(record);    
    QString text = ui->txtEditor->toPlainText();
    QRegularExpressionMatch found_match = re_task_on_timesheet.match(text);
    if (found_match.hasMatch())
    {
        // update time (minutes)
        unsigned int time = found_match.captured(1).toUInt();
        text.replace(re_task_on_timesheet, "\n" + today + "\t\t" + QString::number(++time) + "\t\t" + _recording_task);
    }
    else
    {
        // add task recording at the bottom
        text.append("\n" + today + "\t\t1\t\t" + _recording_task);
    }
    ui->txtEditor->setPlainText(text);

    // move back to last edit position
    QTextCursor cursor = ui->txtEditor->textCursor();
    cursor.setPosition(cursor_position, QTextCursor::MoveAnchor);
    ui->txtEditor->setTextCursor(cursor);
}

void DashBoard::UpdateGUILockscreen(bool active)
{
    if (active == true)
    {
        ui->lblKeepAlive->setVisible(true);
    }
    else
    {
        ui->lblKeepAlive->setVisible(false);
    }
}

void DashBoard::keyPressEvent(QKeyEvent* key_event)
{
    // only key with CTRL are a valid command
    if (key_event->modifiers() == Qt::ControlModifier)
    {
        if (key_event->key() == Qt::Key_H)
        {            
            // <CTRL> + <h> for help and information (the about page)
            QString description = tr("<code>YEt Another Stupid Timetracker<br>"
                                     "(January 2025)<br><br><br>"
                                     "</code>");
            QMessageBox::about(this, tr("YEAST"), description +
                               "<code>" +
                               "CTRL+h ........... show help<br>" +
                               "CTRL+l ........... enable/disable auto screen unlock<br>" +
                               "CTRL+t ........... toggle status (todo, progress, wait, done)<br>" +
                               "CTRL+r ........... start/stop task recording<br>" +
                               "CTRL+s ........... save current text<br>" +
                               "</code>");
        }
        else if ((key_event->key() == Qt::Key_L))
        {
            // <CTRL> + <l> to enable/disable screen unlock
            _ptr_screen_unlock_manager->ToggleActivation();
        }
        else if ((key_event->key() == Qt::Key_T))
        {
            // <CTRL> + <t> to toogle status between [TODO, PROGRESS, WAIT, DONE]
            this->toggleStatus();
        }
        else if ((key_event->key() == Qt::Key_R))
        {
            // <CTRL> + <r> to start/stop recording time on task
            this->recordTask();
        }
        else if ((key_event->key() == Qt::Key_W))
        {
            // <CTRL> + <w> to change GUI aspect
        }
        else if ((key_event->key() == Qt::Key_S))
        {
            // <CTRL> + <s> to save current text
            this->saveFile(k_text_filename);
        }
        else
        {
            // command not managed
        }
    }
}

void DashBoard::toggleStatus(void)
{
    QTextCursor cursor = ui->txtEditor->textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    QString status = cursor.selectedText();
    bool change_status = false;
    if (status=="TODO")
    {
        status = "PROGRESS";
        change_status = true;
    }
    else if ((status=="PROGRESS") || (status=="INPROGRESS") || (status=="IN PROGRESS"))
    {
        status = "WAIT";
        change_status = true;
    }
    else if (status=="WAIT")
    {
        status = "DONE";
        change_status = true;
    }
    else if (status=="DONE")
    {
        status = "TODO";
        change_status = true;
    }

    if (change_status)
    {
        cursor.removeSelectedText();
        cursor.insertText(status);
        cursor.movePosition(cursor.WordLeft);
        ui->txtEditor->setTextCursor(cursor);
    }
}

void DashBoard::recordTask()
{
    QTextCursor cursor = ui->txtEditor->textCursor();
    cursor.select(QTextCursor::LineUnderCursor);
    QString text = cursor.selectedText();

    QRegularExpression re_task(QStringLiteral("^(\\<.*\\>)"));
    QRegularExpressionMatch found_match = re_task.match(text);
    if (found_match.hasMatch())
    {
        if (_recording_task == found_match.captured(0))
        {
            // stop recording
            _recording_task = "";
            _timer_recording_task.stop();
            ui->lblRecording->setVisible(false);
        }
        else
        {
            // start recording
            _recording_task = found_match.captured(0);
            _timer_recording_task.start(k_recording_task_period_ms);
            ui->lblRecording->setVisible(true);
        }
    }
    else
    {
        // stop any recording if active
        if (!_recording_task.isNull())
        {
            _recording_task = "";
            _timer_recording_task.stop();
            ui->lblRecording->setVisible(false);
        }
    }
    ui->lblRecording->setText("  Recording: " + _recording_task + "  ");
}

void DashBoard::openFile(const QString file_path)
{
    QFile text_file(file_path);
    if (text_file.open(QFile::ReadOnly | QFile::Text))
    {
        ui->txtEditor->setPlainText(text_file.readAll());
        qInfo() << "Loaded text from: " << file_path;
        // Periodically save file after opening
        _timer_autosave.start(k_autosave_period_ms);
    }
    else
    {
        qWarning() << "ERR: unable to load default text file";
    }
    text_file.close();
}

void DashBoard::saveFile(const QString file_path)
{
    QFile text_file(file_path);
    if (text_file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream store(&text_file);
        store << ui->txtEditor->toPlainText();
        qInfo() << "Current text saved into: " << file_path;
    }
    else
    {
        qWarning() << "ERR: unable to save into text file";
    }
    text_file.close();
}
