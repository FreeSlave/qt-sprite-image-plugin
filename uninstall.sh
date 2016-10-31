#!/bin/sh

MIME_DIR=$(kde4-config --path xdgdata-mime | cut -d : -f1)
MIME_PACKAGES="$MIME_DIR/packages"
KDE_IMAGEFORMATS="$(kde4-config --path qtplugins | cut -d : -f1)/imageformats"
KDE_SERVICES="$(kde4-config --path services | cut -d : -f1)"
KDE_IMAGEIOFORMATS="$KDE_SERVICES/qimageioplugins"

rm -f "$KDE_IMAGEFORMATS/kimg_qspr.so"
rm -f "$KDE_SERVICES/qsprthumbnail.desktop"
rm -f "$KDE_IMAGEIOFORMATS/qspr.desktop"
rm -f "$KDE_IMAGEIOFORMATS/hlspr.desktop"
rm -f "$KDE_IMAGEIOFORMATS/spr32.desktop"
rm -f "$MIME_PACKAGES/qspr.xml"

update-mime-database "$MIME_DIR"
