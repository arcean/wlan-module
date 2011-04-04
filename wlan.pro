#-------------------------------------------------
#
# Project created by QtCreator 2011-04-04T22:56:00
#
#-------------------------------------------------

QT       += core gui

TARGET = wlan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    WlanMaemo.cpp

HEADERS  += mainwindow.h \
    WlanMaemo.h

FORMS    += mainwindow.ui

CONFIG += mobility11

CONFIG += link_pkgconfig
PKGCONFIG += glib-2.0 liblocation hildon-1 dbus-1

MOBILITY = 

symbian {
    TARGET.UID3 = 0xe22e4a50
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
