#!/bin/sh

KDEBASE="$HOME/.kde"
KDE_IMAGEFORMATS="$KDEBASE/lib/kde4/plugins/imageformats"
KDE_IMAGEIOFORMATS="$KDEBASE/share/kde4/services/imageioplugins"

rm -f "$KDE_IMAGEFORMATS/libqspr.so"
rm -f "$KDE_IMAGEIOFORMATS/qspr.desktop"
