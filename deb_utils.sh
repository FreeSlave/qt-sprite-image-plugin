#!/bin/sh

VERSION=1.1

QT4QSPR=qt4-qspr
QT5QSPR=qt5-qspr
KDE4QSPR=kde4-qspr

BASETGZPATH=/var/cache/pbuilder

FILES="qspr/qspr.pro qspr/spritedefs.cpp qspr/spritedefs.h qspr/qsprhandler.cpp qspr/qsprhandler.h qspr/qsprplugin.cpp qspr/qsprplugin.h qspr/qspr.json qspr/CMakeLists.txt qspr/qspr.xml qspr/qspr.desktop qspr/hlspr.desktop qspr/spr32.desktop qspr/qsprthumbnail.desktop"

ARCHIVE=./deb/qspr_$VERSION.orig.tar.gz

prepare_source()
{
    tar czf "$ARCHIVE" $FILES
    tar xf "$ARCHIVE" --directory ./deb
}

create_source()
{
    local QSPR=$1
    ln -f "$ARCHIVE" ./deb/${QSPR}_${VERSION}.orig.tar.gz
    
    for i in $FILES
    do
        ln -f ./deb/qspr/`basename $i` ./deb/$QSPR/`basename $i`
    done
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
        pbuilder --update --basetgz $BASETGZ --distribution $DISTRO --architecture $ARCH
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
    (cd deb/$QSPR && pdebuild -- --basetgz $(create_basetgz_path "$DISTRO" "$ARCH") ../${QSPR}_${VERSION}-1.dsc )
}

if [ -z $1 ]; then
    echo "Specify actions: sources|pbuilder|packages"
    exit 1
fi

if [ $1 = "sources" ]; then
    echo "Creating sources"
    prepare_source
    create_source "$QT4QSPR"
    create_source "$QT5QSPR"
    create_source "$KDE4QSPR"
elif [ $1 = "pbuilder" ]; then
    echo "Creating/Updating pbuilder chroots"
    
    case "$(uname -m)" in
        *x86_64|amd64)
            create_pbuilder "wheezy" "i386"
            create_pbuilder "jessie" "i386"
            create_pbuilder "wheezy" "amd64"
            create_pbuilder "jessie" "amd64"
            ;;
        *i*86)
            create_pbuilder "wheezy" "i386"
            create_pbuilder "jessie" "i386"
            ;;
        *)
            echo "Script supports only amd64 and i386 pbuilder chroots"
            ;;
    esac
    
elif [ $1 = "packages" ]; then
    echo "Creating packages"
    
    case "$(uname -m)" in
        *x86_64|amd64)
            create_package "wheezy" "i386" "$QT4QSPR"
            create_package "jessie" "i386" "$QT5QSPR"
            create_package "jessie" "i386" "$KDE4QSPR"
            create_package "wheezy" "amd64" "$QT4QSPR"
            create_package "jessie" "amd64" "$QT5QSPR"
            create_package "jessie" "amd64" "$KDE4QSPR"
            ;;
        *i*86)
            create_package "wheezy" "i386" "$QT4QSPR"
            create_package "jessie" "i386" "$QT5QSPR"
            create_package "jessie" "i386" "$KDE4QSPR"
            ;;
        *)
            echo "Script supports only amd64 and i386 pbuilder chroots"
            ;;
    esac
else 
    echo "Specify one of these actions: sources|pbuilder|packages"
    exit 1
fi


