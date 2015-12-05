QImageIOPlugin for Qt that provides support for Half-Life and Quake *.spr files.

## Installing for KDE4

This plugin is specially useful when using with KDE.
After installing Dolphin and Krusader should be able to show sprite previews and Gwenview should be able to show sprite animation.

### Using CMake

Install dependencies (these are for for Debian jessie):

    sudo apt-get install cmake libqt4-dev kdesdk-scripts kdelibs5-dev
    
Building and installing:

    mkdir build && cd build
    cmake -DCMAKE_INSTALL_PREFIX=/usr ../qspr/
    make
    sudo make install
    
Note: it may take some time due to mime database updating.

To uninstall type:

    sudo make uninstall

### Using qmake-qt4 and scripts

Install dependencies (these are for for Debian jessie):

    sudo apt-get install libqt4-dev qt4-qmake
    
Building and installing:

    (cd qspr && qmake-qt4 && make && cd ..)
    ./install.sh
    
To uninstall type:

    ./uninstall.sh
    
