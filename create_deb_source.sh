#!/bin/sh

FILES="qspr/qspr.pro qspr/spritedefs.cpp qspr/spritedefs.h qspr/qsprhandler.cpp qspr/qsprhandler.h qspr/qsprplugin.cpp qspr/qsprplugin.h qspr/qspr.json qspr/CMakeLists.txt qspr/qspr.xml qspr/qspr.desktop qspr/qsprthumbnail.desktop"

VERSION=1.0

ARCHIVE4=./deb/qt4-qspr_$VERSION.orig.tar.gz
ARCHIVE5=./deb/qt5-qspr_$VERSION.orig.tar.gz

ARCHIVE_KDE4=./deb/kde4-qspr_$VERSION.orig.tar.gz

tar czf "$ARCHIVE4" $FILES
tar czf "$ARCHIVE5" $FILES
tar czf "$ARCHIVE_KDE4" $FILES
tar xf "$ARCHIVE4" --directory ./deb

for i in $FILES
do
    ln -f deb/qspr/`basename $i` deb/qt4-qspr/`basename $i`
done

for i in $FILES
do
    ln -f deb/qspr/`basename $i` deb/qt5-qspr/`basename $i`
done

for i in $FILES
do
    ln -f deb/qspr/`basename $i` deb/kde4-qspr/`basename $i`
done
