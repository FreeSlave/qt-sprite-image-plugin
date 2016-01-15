QImageIOPlugin for Qt that provides support for Half-Life and Quake *.spr files.

## Installing for KDE4 or KDE5

This plugin is especially useful when using with KDE. There're several ways to install it (see below).
After plugin is installed Gwenview should be able to show sprite animation.

Note: To enable sprite previews in Dolphin you must enable "Half-Life sprites" in Dolphin General/Previews settings.

### Using qmake and scripts

This method will install plugin only for the current user.

For KDE4:

    # on Debian / Ubuntu:
    sudo apt-get install libqt4-dev qt4-qmake
    # or on Fedora:
    sudo yum install qt-devel # replace yum with dnf for latter Fedora releases
    
    (cd qspr && qmake-qt4 && make)
    ./install.sh
    
Note: On some distros you probably need to edit the install.sh script to use **lib64** directory instead of **lib** in the *KDE_IMAGEFORMATS* variable.
    
For KDE5:

    sudo apt-get install qtbase5-dev qmake
    export QT_SELECT=5 # ensure qmake points to qmake qt version 5.
    (cd qspr && qmake && make)
    ./install.sh
    
To uninstall type:

    ./uninstall.sh

### Using CMake

This method will install plugin globally on the system (for all users).

For KDE4:

    # on Debian / Ubuntu:
    sudo apt-get install cmake libqt4-dev kdelibs5-dev
    # or on Fedora:
    sudo yum install cmake qt-devel kdelibs-devel
    
    ln -f qspr/CMakeLists-KDE4.txt qspr/CMakeLists.txt
    mkdir -p build-kde4 && cd build-kde4
    export QT_SELECT=4
    cmake -DCMAKE_INSTALL_PREFIX=/usr ../qspr/
    make
    sudo make install
    
For KDE5:

    sudo apt-get install cmake qtbase5-dev extra-cmake-modules
    ln -f qspr/CMakeLists-KDE5.txt qspr/CMakeLists.txt
    mkdir -p build-kde5 && cd build-kde5
    export QT_SELECT=5
    cmake -DCMAKE_INSTALL_PREFIX=/usr ../qspr/
    make
    sudo make install

To uninstall type:

    sudo make uninstall
