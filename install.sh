#!/bin/sh

KDEBASE=$(kde4-config --localprefix)
MIME_DIR=$(kde4-config --path xdgdata-mime | cut -d : -f1)

MIME_PACKAGES="$MIME_DIR/packages"
KDE_IMAGEFORMATS="$KDEBASE/lib/kde4/plugins/imageformats"
KDE_SERVICES="$KDEBASE/share/kde4/services"
KDE_IMAGEIOFORMATS="$KDE_SERVICES/qimageioplugins"

if [ ! -d "$MIME_PACKAGES" ]; then
    mkdir -p "$MIME_PACKAGES"
fi

if [ ! -d "$KDE_IMAGEFORMATS" ]; then
    mkdir -p $KDE_IMAGEFORMATS
fi

install -m644 qspr/libqspr.so "$KDE_IMAGEFORMATS/kimg_qspr.so"
install -m644 qspr/qsprthumbnail.desktop "$KDE_SERVICES"
install -m644 qspr/qspr.desktop "$KDE_IMAGEIOFORMATS"
install -m644 qspr/hlspr.desktop "$KDE_IMAGEIOFORMATS"
install -m644 qspr/spr32.desktop "$KDE_IMAGEIOFORMATS"
install -m644 qspr/qspr.xml "$MIME_PACKAGES"
update-mime-database "$MIME_DIR"
