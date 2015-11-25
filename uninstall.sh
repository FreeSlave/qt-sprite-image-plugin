#!/bin/sh

KDEBASE="$HOME/.kde"
KDE_IMAGEFORMATS="$KDEBASE/lib/kde4/plugins/imageformats"
KDE_SERVICES="$KDEBASE/share/kde4/services"
KDE_IMAGEIOFORMATS="$KDE_SERVICES/imageioplugins"

rm -f "$KDE_IMAGEFORMATS/libqspr.so"
rm -f "$KDE_SERVICES/qsprthumbnail.desktop"
rm -f "$KDE_IMAGEIOFORMATS/qspr.desktop"
