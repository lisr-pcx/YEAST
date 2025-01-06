QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    highlight.cpp \
    main.cpp \
    dashboard.cpp \
    screen_unlock.cpp

HEADERS += \
    dashboard.h \
    global.h \
    highlight.h \
    screen_unlock.h

FORMS += \
    dashboard.ui

RC_ICONS = yeast.ico

# Version of the software
VERSION_MAJOR = 0
VERSION_MINOR = 6

DEFINES +=  "VERSION_MAJOR=$$VERSION_MAJOR"\
            "VERSION_MINOR=$$VERSION_MINOR"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
