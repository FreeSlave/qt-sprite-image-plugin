Name:           kde4-qspr
Version:        1.2
Release:        1%{?dist}
Summary:        KDE4 image format plugin for Half-Life and Quake sprites

License:        LGPLv2
URL:            https://bitbucket.org/FreeSlave/qt-sprite-image-plugin
Source0:        https://bitbucket.org/FreeSlave/qt-sprite-image-plugin/get/%{name}-%{version}.tar.gz

BuildRequires:  gcc-c++ cmake qt-devel kdelibs-devel

%description
kde4-qspr is KDE4 image format plugin 
for Half-Life and Quake sprites.

%prep
%setup -q

%post
/bin/touch --no-create %{_datadir}/mime/packages &>/dev/null || :

%postun
if [ $1 -eq 0 ] ; then
  /usr/bin/update-mime-database %{_datadir}/mime &> /dev/null || :
fi

%posttrans
/usr/bin/update-mime-database %{?fedora:-n} %{_datadir}/mime &> /dev/null || :

%build
%cmake .
make %{?_smp_mflags}

%install
make DESTDIR=%{buildroot} install

%files
%{_libdir}/kde4/plugins/imageformats/kimg_qspr.so
%{_datadir}/mime/packages/qspr.xml
%{_datadir}/kde4/services/qimageioplugins/qspr.desktop
%{_datadir}/kde4/services/qimageioplugins/spr32.desktop
%{_datadir}/kde4/services/qimageioplugins/hlspr.desktop
%{_datadir}/kde4/services/qsprthumbnail.desktop

%changelog
* Tue May 31 2016 Roman Chistokhodov 1.2-1
- Initial release
