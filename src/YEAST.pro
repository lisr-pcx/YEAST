QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db_manager.cpp \
    history.cpp \
    main.cpp \
    dashboard.cpp \
    screen_unlock.cpp \
    single_record.cpp \
    singletask.cpp \
    timetracker_manager.cpp

HEADERS += \
    dashboard.h \
    db_manager.h \
    global.h \
    history.h \
    screen_unlock.h \
    single_record.h \
    singletask.h \
    timetracker_manager.h

FORMS += \
    dashboard.ui \
    history.ui

RC_ICONS = yeast.ico

# Version of the software
VERSION_MAJOR = 0
VERSION_MINOR = 5

DEFINES +=  "VERSION_MAJOR=$$VERSION_MAJOR"\
            "VERSION_MINOR=$$VERSION_MINOR"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
