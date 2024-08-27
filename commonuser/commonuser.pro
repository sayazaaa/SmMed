#-------------------------------------------------
#
# Project created by QtCreator 2020-09-02T22:09:28
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++9


RC_ICONS = logo.ico

TARGET = commonuser
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

SOURCES += $$files(./*.cpp)

HEADERS += $$files(./*.h)

FORMS += $$files(./*.ui)

INCLUDEPATH += $$PWD

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qss.qrc





win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../shared/release/ -lshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../shared/debug/ -lshared
else:unix: LIBS += -L$$OUT_PWD/../shared/ -lshared

INCLUDEPATH += $$PWD/../shared/include/ \
               $$PWD/../shared/
DEPENDPATH += $$PWD/../shared/include/ \
               $$PWD/../shared/

INCLUDEPATH += /usr/include/botan-2

LIBS += -lbotan-2



unix:!macx: LIBS += -L$$OUT_PWD/../dataclass/ -ldataclass

INCLUDEPATH += $$PWD/../dataclass
DEPENDPATH += $$PWD/../dataclass
