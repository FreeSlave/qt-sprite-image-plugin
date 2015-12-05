#!/bin/sh

if [ $EUID -ne 0 ]; then
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

KDE_IMAGEFORMATS="$KDEBASE/lib/kde4/plugins/imageformats"
KDE_SERVICES="$KDEBASE/share/kde4/services"
KDE_IMAGEIOFORMATS="$KDE_SERVICES/qimageioplugins"

rm -f "$KDE_IMAGEFORMATS/kimg_qspr.so"
rm -f "$KDE_SERVICES/qsprthumbnail.desktop"
rm -f "$KDE_IMAGEIOFORMATS/qspr.desktop"
rm -f "$MIME_PACKAGES/qspr.xml"

update-mime-database "$MIME_DIR"
