TEMPLATE = subdirs

SUBDIRS += \
    commonuser \
    db_client \
    doctor \
    server
HEADERS += share/include/netclient.h \
            share/include/dbserver.h \
            share/include/netloader.h
SOURCES += share/src/netclient.cpp \
            share/src/dbserver.cpp \
            share/src/netloader.cpp

