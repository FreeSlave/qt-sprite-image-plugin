#!/bin/sh

if [ $(id -u) -ne 0 ]; then
   KDEBASE="$HOME/.kde4"
   
   if [ ! -d "$KDEBASE" ]; then
       KDEBASE="$HOME/.kde"
   fi
   
   MIME_DIR=${XDG_DATA_HOME:-$HOME/.local/share}/mime
else
   KDEBASE="/usr/local"
   MIME_DIR="/usr/local/share/mime"
fi

if [ ! -d "$KDEBASE" ]; then
    echo "Could not find base kde directory"
fi

MIME_PACKAGES="$MIME_DIR/packages"

if [ ! -d "$MIME_PACKAGES" ]; then
    mkdir -p "$MIME_PACKAGES"
fi

KDE_IMAGEFORMATS="$KDEBASE/lib/kde4/plugins/imageformats"
KDE_SERVICES="$KDEBASE/share/kde4/services"
KDE_IMAGEIOFORMATS="$KDE_SERVICES/qimageioplugins"

if [ ! -d "$KDE_IMAGEFORMATS" ]; then
    mkdir -p $KDE_IMAGEFORMATS
fi

if [ ! -d "$KDE_IMAGEIOFORMATS" ]; then
    mkdir -p $KDE_IMAGEIOFORMATS
fi

install -m644 qspr/libqspr.so $KDE_IMAGEFORMATS/kimg_qspr.so
install -m644 qspr/qsprthumbnail.desktop $KDE_SERVICES
install -m644 qspr/qspr.desktop $KDE_IMAGEIOFORMATS
install -m644 qspr/qspr.xml "$MIME_PACKAGES"
update-mime-database "$MIME_DIR"
