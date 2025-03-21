QT += core network widgets

TEMPLATE = lib
DEFINES += SHARED_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH +=  include \
                /usr/include/mysql  \
                /usr/include/botan-2 \
                /usr/include/botan \
                /usr/include/uuid \
                /usr/include/c++/9 \
                /usr/include/c++/7 \
                /usr/include/uuid

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES +=  shared.cpp \
            $$files(src/*.cpp)
HEADERS +=  shared.h \
            $$files(include/*.h) \
            sharedglobal.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -lmysqlpp
unix|win32: LIBS += -lbotan-2



unix:!macx: LIBS += -L$$OUT_PWD/../dataclass/ -ldataclass

INCLUDEPATH += $$PWD/../dataclass
DEPENDPATH += $$PWD/../dataclass
