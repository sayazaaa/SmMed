TEMPLATE = subdirs

#SUBDIRS += \
#    commonuser \
#    doctor \
#    shared \
#    dataclass

SUBDIRS += \
    commonuser \
    dataclass \
    dbclient \
    doctor \
    shared

shared.depends = dataclass

commonuser.depends = shared
dbclient.depends = shared
doctor.depends = shared

