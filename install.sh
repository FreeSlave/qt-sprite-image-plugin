#!/bin/sh

KDEBASE="$HOME/.kde"
KDE_IMAGEFORMATS="$KDEBASE/lib/kde4/plugins/imageformats"
KDE_SERVICES="$KDEBASE/share/kde4/services"
KDE_IMAGEIOFORMATS="$KDE_SERVICES/imageioplugins"

if [ ! -d "$KDE_IMAGEFORMATS" ]; then
    mkdir -p $KDE_IMAGEFORMATS
fi

if [ ! -d "$KDE_IMAGEIOFORMATS" ]; then
    mkdir -p $KDE_IMAGEIOFORMATS
fi

libqspr=$(find build*Release/ -name libqspr.so -type f)

install -m644 $libqspr $KDE_IMAGEFORMATS
install -m644 kde4/services/qsprthumbnail.desktop $KDE_SERVICES
install -m644 kde4/services/imageioplugins/qspr.desktop $KDE_IMAGEIOFORMATS
