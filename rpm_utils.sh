#!/bin/sh

VERSION=1.2

QT4QSPR=qt4-qspr
QT5QSPR=qt5-qspr
KDE4QSPR=kde4-qspr
KDE5QSPR=kde5-qspr

COMMON_FILES="qspr/spritedefs.cpp qspr/spritedefs.h qspr/qsprhandler.cpp qspr/qsprhandler.h qspr/qsprplugin.cpp qspr/qsprplugin.h"

TARGET_DIR="$HOME/rpmbuild"

QTSPR="$1"

if [ ! -z "$2" ]; then
    TARGET_DIR="$2"
fi

create_source()
{
    local QSPR=$1
    local FILES=$2
    local TAR_OPTIONS=$3
    
    local ARCHIVE="./rpm/$QSPR-$VERSION.tar.gz"
    
    tar czf "$ARCHIVE" --transform="flags=r;s|qspr/|$QSPR-$VERSION/|" $TAR_OPTIONS $FILES
    mv "$ARCHIVE" "$TARGET_DIR/SOURCES"
    cp "rpm/$QSPR.spec" "$TARGET_DIR/SPECS"
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

create_packages()
{
    local QSPR=$1
    local VENDOR=$2
    local BASE=$3
    
    case "$(uname -m)" in
        *x86_64|amd64)
            create_package "$BASE-x86_64" "$QSPR" "$VENDOR"
            ;;
    esac

#     case "$(uname -m)" in
#        *x86_64|amd64|*i*86)
#            create_package "$BASE-i386" "$QSPR" "$VENDOR"
#            ;;
#     esac
}

if [ "$QTSPR" = qt4 ]; then
    create_source "$QT4QSPR" "$COMMON_FILES qspr/qspr.pro" --transform=''
    create_packages "$QT4QSPR" el6 epel-6
elif [ "$QTSPR" = qt5 ]; then
    create_source "$QT5QSPR" "$COMMON_FILES qspr/qspr.pro qspr/qspr.json" --transform=''
    create_packages "$QT5QSPR" el6 epel-6
elif [ "$QTSPR" = kde4 ]; then
    KDE4_FILES="qspr/qspr.xml qspr/qspr.desktop qspr/hlspr.desktop qspr/spr32.desktop qspr/qsprthumbnail.desktop qspr/CMakeLists-KDE4.txt"
    create_source "$KDE4QSPR" "$COMMON_FILES $KDE4_FILES" --transform='flags=r;s|CMakeLists-KDE4.txt|CMakeLists.txt|'
    create_packages "$KDE4QSPR" fc19 fedora-19
elif [ "$QTSPR" = kde5 ]; then
    KDE5_FILES="qspr/qspr.xml qspr/qspr.json qspr/qspr.desktop qspr/hlspr.desktop qspr/spr32.desktop qspr/qsprthumbnail.desktop qspr/CMakeLists-KDE5.txt"
    create_source "$KDE5QSPR" "$COMMON_FILES $KDE5_FILES" --transform='flags=r;s|CMakeLists-KDE5.txt|CMakeLists.txt|'
    create_packages "$KDE5QSPR" fc23 fedora-23
else
    echo "Unknown target. Known targets are: qt4, qt5, kde4, kde5"
fi
