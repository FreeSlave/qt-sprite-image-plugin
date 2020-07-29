cmake_minimum_required(VERSION 2.8.12)

project(qspr)

include(FeatureSummary)
find_package(ECM 5.9.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

include(CheckIncludeFiles)

set(REQUIRED_QT_VERSION 5.0.0)
find_package(Qt5Gui ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(libqspr_LIB_SRCS qspr/qsprhandler.cpp qspr/qsprplugin.cpp qspr/spritedefs.cpp)
add_library(libqspr MODULE ${libqspr_LIB_SRCS})
target_link_libraries(libqspr Qt5::Gui)

install(TARGETS libqspr DESTINATION ${KDE_INSTALL_LIBDIR}/qt5/plugins/imageformats/) # KDE_INSTALL_QTPLUGINDIR has path without qt5 for some reason
install(DIRECTORY services/ DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
