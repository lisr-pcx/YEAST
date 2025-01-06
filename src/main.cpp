//============================================================================
// Name        : main.cpp
// Author      : F.Tessarollo
// Version     : 0.5
//
// YE.A.S.T
// (YEt Another Stupid Timetracker)
// Please refer to README.md
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
