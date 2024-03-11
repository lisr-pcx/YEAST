//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================

#include "userlogger.h"

bool UserLogger::is_available_ = false;
QFile* UserLogger::ptr_log_file_ = Q_NULLPTR;
QHash<QtMsgType, QString> UserLogger::context_names_ =
{
    {QtMsgType::QtDebugMsg,     " Debug "   },
    {QtMsgType::QtInfoMsg,		" Info "    },
    {QtMsgType::QtWarningMsg,	" Warning " },
    {QtMsgType::QtCriticalMsg,	" Critical "},
    {QtMsgType::QtFatalMsg,		" Fatal "   }
};

void UserLogger::Start()
{
    if (is_available_ == false)
    {
        UserLogger::ptr_log_file_ = new QFile;
        UserLogger::ptr_log_file_->setFileName("./YEAST.log");
        UserLogger::ptr_log_file_->open(QFile::WriteOnly | QIODevice::Append);

        // redirect debug msg to file
        qInstallMessageHandler(UserLogger::WriteLog);

        // clear the log file
        UserLogger::ptr_log_file_->resize(0);

        UserLogger::is_available_ = true;
    }
}

void UserLogger::WriteLog(QtMsgType msg_type,
                          const QMessageLogContext& msg_context,
                          const QString& text)
{
    if ( (UserLogger::ptr_log_file_ != Q_NULLPTR) &&
         (UserLogger::is_available_ == true) )
    {
        QString log = QObject::tr("%1; %2; %3; %4; %5; %6\n").
                arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).
                arg(UserLogger::context_names_.value(msg_type)).
                arg(msg_context.line).
                arg(QString(msg_context.file).
                    section('\\', -1)).
                arg(QString(msg_context.function).
                    section('(', -2, -2).
                    section(' ', -1).
                    section(' ', -1)).
                arg(text);
        UserLogger::ptr_log_file_->write(log.toLocal8Bit());
        UserLogger::ptr_log_file_->flush();
    }
}

void UserLogger::End()
{
    if (UserLogger::ptr_log_file_ != Q_NULLPTR)
    {
        UserLogger::ptr_log_file_->close();
        delete ptr_log_file_;
        UserLogger::ptr_log_file_ = Q_NULLPTR;

        UserLogger::is_available_ = false;
    }
}
