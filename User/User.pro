QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = logo.ico

TARGET = User
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    login.cpp \
        main.cpp \
        widget.cpp \
    appinit.cpp \
    mymessagebox.cpp

HEADERS += \
    login.h \
        widget.h \
    appinit.h \
    mymessagebox.h

FORMS += \
    login.ui \
        widget.ui \
    mymessagebox.ui

RESOURCES += \
    qss.qrc
