#!/bin/sh

VERSION=1.2

QT4QSPR=qt4-qspr
QT5QSPR=qt5-qspr
KDE4QSPR=kde4-qspr
KDE5QSPR=kde5-qspr

BASETGZPATH=/var/cache/pbuilder

# DEBIAN_MIRROR="ftp://ftp.cz.debian.org/debian/"
# DEBIAN_PBUILDER_OPTIONS="--mirror $DEBIAN_MIRROR --debootstrapopts --keyring=/usr/share/keyrings/debian-archive-keyring.gpg"

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

create_pbuilder()
{
    local DISTRO=$1
    local ARCH=$2
    local BASETGZ=$(create_basetgz_path "$1" "$2")
    
    if [ -f $BASETGZ ]; then
        echo "Updating $BASETGZ"
        pbuilder --update --basetgz $BASETGZ --distribution $DISTRO --architecture $ARCH --override-config
    else
        echo "Creating $BASETGZ"
        pbuilder create --basetgz $BASETGZ --distribution $DISTRO --architecture $ARCH
    fi
}

create_package()
{
    local DISTRO=$1
    local ARCH=$2
    local QSPR=$3
    
    (cd deb/$QSPR && dpkg-source -b .)
    # TODO: try --use-pdebuild-internal
    (cd deb/$QSPR && mkdir -p ../../result && pdebuild --buildresult ../../result -- --basetgz $(create_basetgz_path "$DISTRO" "$ARCH") ../${QSPR}_${VERSION}-1.dsc )
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
            create_pbuilder "precise" "amd64"
            create_pbuilder "trusty" "amd64"
            create_pbuilder "vivid" "amd64"
            ;;
    esac
    
    case "$(uname -m)" in
        *x86_64|amd64|*i*86)
            create_pbuilder "precise" "i386"
            create_pbuilder "trusty" "i386"
            create_pbuilder "vivid" "i386"
            ;;
    esac
    
elif [ $1 = "packages" ]; then
    echo "Creating packages"
    
    case "$(uname -m)" in
        *x86_64|amd64)
            create_package "precise" "amd64" "$QT4QSPR"
            create_package "trusty" "amd64" "$QT5QSPR"
            create_package "trusty" "amd64" "$KDE4QSPR"
            create_package "vivid" "amd64" "$KDE5QSPR"
            ;;
    esac
    
    case "$(uname -m)" in
        *x86_64|amd64|*i*86)
            create_package "precise" "i386" "$QT4QSPR"
            create_package "trusty" "i386" "$QT5QSPR"
            create_package "trusty" "i386" "$KDE4QSPR"
            create_package "vivid" "i386" "$KDE5QSPR"
            ;;
    esac    

else 
    echo "Specify one of these actions: sources|pbuilder|packages"
    exit 1
fi


