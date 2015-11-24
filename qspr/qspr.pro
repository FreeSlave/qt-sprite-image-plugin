#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T16:16:22
#
#-------------------------------------------------

QT       += core gui

TARGET = qspr
TEMPLATE = lib
CONFIG += plugin

#DESTDIR = $$[QT_INSTALL_PLUGINS]/imageformats

SOURCES += qsprplugin.cpp \
    qsprhandler.cpp \
    spritedefs.cpp

HEADERS += qsprplugin.h \
    qsprhandler.h \
    spritedefs.h
OTHER_FILES += qspr.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
