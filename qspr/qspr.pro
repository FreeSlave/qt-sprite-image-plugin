#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T16:16:22
#
#-------------------------------------------------

QT       += core gui

TARGET = qspr
TEMPLATE = lib
CONFIG += plugin

SOURCES += qsprplugin.cpp \
    qsprhandler.cpp \
    spritedefs.cpp

HEADERS += qsprplugin.h \
    qsprhandler.h \
    spritedefs.h
OTHER_FILES += qspr.json \
    qspr.desktop \
    qsprthumbnail.desktop \
    qspr.xml \
    spr32.desktop \
    hlspr.desktop

unix {
    target.path = $$[QT_INSTALL_PLUGINS]/imageformats
    INSTALLS += target
}
