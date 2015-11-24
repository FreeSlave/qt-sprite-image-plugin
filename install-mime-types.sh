#!/bin/sh

MIME_HOME=${XDG_DATA_HOME:-$HOME/.local/share}/mime
MIME_PACKAGES_HOME="$MIME_HOME"/packages

if [ ! -d "$MIME_PACKAGES_HOME" ]; then
    mkdir -p "$MIME_PACKAGES_HOME"
fi

cp ./mime/packages/qspr.xml "$MIME_PACKAGES_HOME"
update-mime-database "$MIME_HOME"
