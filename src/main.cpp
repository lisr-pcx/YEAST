//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// Description : Entry point
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QString>
#include "global.h"
#include "dashboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    // Load stylesheet
//    QFile stylesheet_file(QDir().currentPath() + "/" + k_stylesheet_filename);
//    if (stylesheet_file.open(QFile::ReadOnly))
//    {
//        QString text_style = QLatin1String(stylesheet_file.readAll());
//        a.setStyleSheet(text_style);
//    }

    DashBoard w;
    w.show();

    return a.exec();
}
