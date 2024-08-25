TEMPLATE = subdirs

SUBDIRS += \
    commonuser \
    dataclass \
    dbclient \
    doctor \
    shared

# shared.depends = dataclass

# commonuser.depends = shared dataclass
# dbclient.depends = shared
# doctor.depends = shared
# server.depends = shared

