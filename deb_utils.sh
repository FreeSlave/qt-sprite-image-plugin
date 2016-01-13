#!/bin/sh

VERSION=1.1

QT4QSPR=qt4-qspr
QT5QSPR=qt5-qspr
KDE4QSPR=kde4-qspr
KDE5QSPR=kde5-qspr

BASETGZPATH=/var/cache/pbuilder

FILES="qspr/spritedefs.cpp qspr/spritedefs.h qspr/qsprhandler.cpp qspr/qsprhandler.h qspr/qsprplugin.cpp qspr/qsprplugin.h qspr/qspr.json  qspr/qspr.xml qspr/qspr.desktop qspr/hlspr.desktop qspr/spr32.desktop qspr/qsprthumbnail.desktop"

create_source()
{
    local QSPR=$1
    local PROJECT=$2
    local TAR_OPTIONS=$3
    
    local ARCHIVE="./deb/${QSPR}_${VERSION}.orig.tar.gz"
    
    tar czf "$ARCHIVE" --transform="flags=r;s|qspr/|$QSPR/|"  $TAR_OPTIONS $FILES $PROJECT
    tar xf "$ARCHIVE" --directory ./deb
}

create_basetgz_path()
{
    echo "$BASETGZPATH/$1-$2.tgz"
}

PBUILDER_OPTIONS="--mirror ftp://ftp.us.debian.org/debian/ --debootstrapopts --keyring=/usr/share/keyrings/debian-archive-keyring.gpg"

create_pbuilder()
{
    local DISTRO=$1
    local ARCH=$2
    local BASETGZ=$(create_basetgz_path "$1" "$2")
    
    if [ -f $BASETGZ ]; then
        echo "Updating $BASETGZ"
        pbuilder --update --basetgz $BASETGZ --distribution $DISTRO --architecture $ARCH $PBUILDER_OPTIONS
    else
        echo "Creating $BASETGZ"
        pbuilder create --basetgz $BASETGZ --distribution $DISTRO --architecture $ARCH $PBUILDER_OPTIONS
    fi
}

create_package()
{
    local DISTRO=$1
    local ARCH=$2
    local QSPR=$3
    
    (cd deb/$QSPR && dpkg-source -b .)
    (cd deb/$QSPR && pdebuild -- --basetgz $(create_basetgz_path "$DISTRO" "$ARCH") ../${QSPR}_${VERSION}-1.dsc )
}

if [ -z $1 ]; then
    echo "Specify actions: sources|pbuilder|packages"
    exit 1
fi

if [ $1 = "sources" ]; then
    echo "Creating sources"
    create_source "$QT4QSPR" "qspr/qspr.pro" --transform=''
    create_source "$QT5QSPR" "qspr/qspr.pro" --transform=''
    create_source "$KDE4QSPR" "qspr/CMakeLists-KDE4.txt" --transform='flags=r;s|CMakeLists-KDE4.txt|CMakeLists.txt|'
    create_source "$KDE5QSPR" "qspr/CMakeLists-KDE5.txt" --transform='flags=r;s|CMakeLists-KDE5.txt|CMakeLists.txt|'
elif [ $1 = "pbuilder" ]; then
    echo "Creating/Updating pbuilder chroots"
    
    case "$(uname -m)" in
        *x86_64|amd64)
            create_pbuilder "wheezy" "amd64"
            create_pbuilder "jessie" "amd64"
            create_pbuilder "stretch" "amd64"
            ;;
    esac
    
    case "$(uname -m)" in
        *x86_64|amd64|*i*86)
            create_pbuilder "wheezy" "i386"
            create_pbuilder "jessie" "i386"
            create_pbuilder "stretch" "i386"
            ;;
    esac
    
elif [ $1 = "packages" ]; then
    echo "Creating packages"
    
    case "$(uname -m)" in
        *x86_64|amd64)
            create_package "wheezy" "amd64" "$QT4QSPR"
            create_package "jessie" "amd64" "$QT5QSPR"
            create_package "jessie" "amd64" "$KDE4QSPR"
            create_package "stretch" "amd64" "$KDE5QSPR"
            ;;
    esac
    
    case "$(uname -m)" in
        *x86_64|amd64|*i*86)
            create_package "wheezy" "i386" "$QT4QSPR"
            create_package "jessie" "i386" "$QT5QSPR"
            create_package "jessie" "i386" "$KDE4QSPR"
            create_package "stretch" "i386" "$KDE5QSPR"
            ;;
    esac    

else 
    echo "Specify one of these actions: sources|pbuilder|packages"
    exit 1
fi


