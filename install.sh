#!/bin/sh

KDEBASE="$HOME/.kde"
KDE_IMAGEFORMATS="$KDEBASE/lib/kde4/plugins/imageformats"
KDE_IMAGEIOFORMATS="$KDEBASE/share/kde4/services/imageioplugins"

if [ ! -d "$KDE_IMAGEFORMATS" ]; then
    mkdir -p $KDE_IMAGEFORMATS
fi

if [ ! -d "$KDE_IMAGEIOFORMATS" ]; then
    mkdir -p $KDE_IMAGEIOFORMATS
fi

libqspr=$(find build*Release/ -name libqspr.so -type f)

install -m644 $libqspr $KDE_IMAGEFORMATS
install -m644 qspr/qspr.desktop $KDE_IMAGEIOFORMATS
