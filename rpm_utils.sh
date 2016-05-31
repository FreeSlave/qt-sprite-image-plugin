#!/bin/sh

VERSION=1.2

QT4QSPR=qt4-qspr
QT5QSPR=qt5-qspr
KDE4QSPR=kde4-qspr
KDE5QSPR=kde5-qspr

COMMON_FILES="qspr/spritedefs.cpp qspr/spritedefs.h qspr/qsprhandler.cpp qspr/qsprhandler.h qspr/qsprplugin.cpp qspr/qsprplugin.h"

TARGET_DIR="$HOME/rpmbuild"

if [ ! -z "$1" ]; then
    TARGET_DIR="$1"
fi

create_source()
{
    local QSPR=$1
    local FILES=$2
    local TAR_OPTIONS=$3
    
    local ARCHIVE="./rpm/$QSPR-$VERSION.tar.gz"
    
    tar czf "$ARCHIVE" --transform="flags=r;s|qspr/|$QSPR-$VERSION/|" $FILES
    mv "$ARCHIVE" "$TARGET_DIR/SOURCES"
    cp rpm/qt4-qspr.spec "$TARGET_DIR/SPECS"
}

create_package()
{
    local CONFIGURATION=$1
    local QSPR=$2
    local VENDOR=$3
    local SRCRPM="$QSPR-$VERSION-1.$VENDOR.src.rpm"
    
    mock --resultdir="$TARGET_DIR/SRPMS" -r "$CONFIGURATION" --buildsrpm --spec "$TARGET_DIR/SPECS/$QSPR.spec" --sources "$TARGET_DIR/SOURCES/$QSPR-$VERSION.tar.gz"
    mock --resultdir="$TARGET_DIR/$QSPR/$CONFIGURATION" -r "$CONFIGURATION" "$TARGET_DIR/SRPMS/$SRCRPM"
}


create_source "$QT4QSPR" "$COMMON_FILES qspr/qspr.pro" --transform=''

case "$(uname -m)" in
    *x86_64|amd64)
        create_package "epel-6-x86_64" "$QT4QSPR" el6
        ;;
esac

case "$(uname -m)" in
    *x86_64|amd64|*i*86)
        create_package "epel-6-i386" "$QT4QSPR" el6
        ;;
esac   
