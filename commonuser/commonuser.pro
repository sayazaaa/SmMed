#-------------------------------------------------
#
# Project created by QtCreator 2020-09-02T22:09:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = logo.ico

TARGET = PeachDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    aboutjson.cpp \
    framelesswidget.cpp \
    information.cpp \
    login.cpp \
        main.cpp \
    user_register.cpp \
        widget.cpp \
    mymessagebox.cpp

HEADERS += \
    aboutjson.h \
    framelesswidget.h \
    information.h \
    login.h \
    user_register.h \
        widget.h \
    mymessagebox.h

FORMS += \
    information.ui \
    login.ui \
    user_register.ui \
        widget.ui \
    mymessagebox.ui

RESOURCES += \
    qss.qrc
