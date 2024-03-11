//============================================================================
// Name        : main.cpp
// Author      : F.Tessarollo
// Version     : 0.5
//
// YE.A.S.T
// (YEt Another Small Timetracker)
// Please refer to README.md
//============================================================================

#include <QApplication>
#include <QDebug>
#include "dashboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DashBoard w;
    w.show();    

    return a.exec();
}
