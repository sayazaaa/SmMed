QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_ICONS = logo.ico

TARGET = commonuser
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

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
