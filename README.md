**QImageIOPlugin** for Qt that provides support for Half-Life and Quake *.spr files.

This plugin is especially useful when using with KDE.
After plugin is installed Gwenview should be able to show sprite images.

Note: [qhl-mimetypes](https://github.com/FreeSlave/qhl-mimetypes) must be installed in order to provide MIME type definitions, so KDE apps could handle the sprite files correctly. Look at [OBS packages](https://software.opensuse.org//download.html?project=home%3AFreeSlave&package=qhl-mimetypes).
Another note: To enable sprite previews in Dolphin you must enable "Half-Life sprites" in Dolphin General/Previews settings.

### Build and install

This method will install plugin globally on the system (for all users).

    sudo apt-get install cmake qtbase5-dev extra-cmake-modules
    mkdir -p build && cd build
    export QT_SELECT=5
    cmake -DCMAKE_INSTALL_PREFIX=/usr ..
    make
    sudo make install

To uninstall type:

    sudo make uninstall

