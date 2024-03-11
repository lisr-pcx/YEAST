//============================================================================
// Project     : YE.A.S.T (YEt Another Simple Timetracker)
// Name        : userlogger.h
// Description : Class used to manage and save logs to file
//             :
//             : Implements Google C++ Style Guide, see
//             : https://google.github.io/styleguide/cppguide.html
// Changes     :
// 2023-05-11  : Created
//============================================================================

#ifndef USERLOGGER_H
#define USERLOGGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QHash>
#include <QString>
#include <QDateTime>

class UserLogger
{
public:
    static void Start();
    static void End();
    static void WriteLog(QtMsgType msg_type,
                         const QMessageLogContext& msg_context,
                         const QString& text);

private:
    UserLogger();
    static bool                         is_available_;
    static QFile*                       ptr_log_file_;
    static QHash<QtMsgType, QString>    context_names_;
};

#endif // USERLOGGER_H
