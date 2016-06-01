Name:           qt5-qspr
Version:        1.2
Release:        1%{?dist}
Summary:        Qt5 image format plugin for Half-Life and Quake sprites

License:        LGPLv2
URL:            https://bitbucket.org/FreeSlave/qt-sprite-image-plugin
Source0:        https://bitbucket.org/FreeSlave/qt-sprite-image-plugin/get/%{name}-%{version}.tar.gz

BuildRequires:  gcc-c++ qt5-qtbase-devel

%description
qt5-qspr is Qt5 image format plugin 
for Half-Life and Quake sprites.

%prep
%setup -q

%build
qmake-qt5 QMAKE_CXXFLAGS+="%optflags"
make %{?_smp_mflags}

%install
make INSTALL_ROOT=%{buildroot} install

%files
%{_libdir}/qt5/plugins/imageformats/libqspr.so

%changelog
* Tue May 31 2016 Roman Chistokhodov 1.2-1
- Initial release
