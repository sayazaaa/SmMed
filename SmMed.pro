TEMPLATE = subdirs

SUBDIRS += \
    commonuser \
    dataclass \
    dbclient \
    doctor \
    server \
    shared

shared.depends = dataclass

commonuser.depends = shared
dbclient.depends = shared
doctor.depends = shared
server.depends = shared

