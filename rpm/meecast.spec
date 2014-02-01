# 
# Do not Edit! Generated by:
# spectacle version 0.18
# 
# >> macros
#%define wantmeegopanel 0
#%define all_x86 i386 i586 i686 %{ix86}
#%define all_arm %{arm}
# << macros
%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}

Name:       harbour-meecast
Summary:    Weather forecast application for SailfishOS
Version:    0.8.8
Release:    1
Group:      Utility
License:    GPLv2.1
URL:        https://github.com/Meecast/meecast 
Source0:    %{name}-%{version}.tar.bz2
#Temporary
#Requires:       libmeegotouch-devel
BuildRequires:  pkgconfig(sailfishapp)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(qdeclarative5-boostable)
BuildRequires:  desktop-file-utils
BuildRequires:  pkgconfig(libcurl)
BuildRequires:  pkgconfig(sqlite3)
#BuildRequires:  pkgconfig(gconf-2.0)
BuildRequires:  pkgconfig(dbus-glib-1)
#BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  libxml2-devel
BuildRequires:  gettext
#BuildRequires:  libqt-devel
BuildRequires: qt5-qtpositioning-devel
Requires:      qt5-qtpositioning 
Requires:      sailfishsilica-qt5
Requires:      qt5-qtdeclarative-import-models2 

%description
MeeCast - multiplatform highly customizable open source weather forecast client based on OMWeather code



%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
#export PATH=/usr/lib/qt4/bin:$PATH
%qtc_qmake5
%qtc_make %{?_smp_mflags}
#make
# << build pre


# >> build post
# << build post
%install
rm -rf %{buildroot}
# >> install pre
# << install pre

# >> install post
%qmake5_install
#make INSTALL_ROOT=%{buildroot} install
#rm %{buildroot}/opt/com.meecast.omweather/lib/libomweather-core.a
# << install post
desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop


%files
%defattr(-,root,root,-)
/usr/share/applications/harbour-meecast.desktop
/usr/bin/harbour-meecast
/usr/share/harbour-meecast
#/usr/share/iconsets
/usr/share/icons/hicolor/86x86/apps
#/opt/com.meecast.omweather/share

%changelog
* Tue Jan 26 2014  Vlad Vasilyeu <vasvlad@gmail.com> 0.8.8.1
  * Fixed problem with long text in last update string
* Tue Jan 26 2014  Vlad Vasilyeu <vasvlad@gmail.com> 0.8.7.1
  * Added Wind speed and Wind direction to Cover Page
  * Added text 'Now' to Cover Page
  * Polished Cover Page
* Tue Jan 23 2014  Vlad Vasilyeu <vasvlad@gmail.com> 0.8.6.1
  * Removed button refresh from main form and add Item menu 'Update' to pulley menu 
  * Redesigned form for delete location
  * Fixed problem with transparency Cover window and font size on Cover Window
  * Added last update information on Cover Page
  * Added new icons from Stephan Beyerle (Thank you very much Stephan)
  * Added background Image to Cover (Thank you very much Stephan again)
* Sun Jan 19 2014  Vlad Vasilyeu <vasvlad@gmail.com> 0.8.5
  * Fixed various small problems
  * Fixed problem with size of font in CoverPage
  * Fixed problem with scroll down for hours in FullWeather page
  * Added possibility to refresh weather forecast using the CoverPage
  * Fixed problem with open many applications(MeeCast) when you click the icon 
* Sat Jan 18 2014  Vlad Vasilyeu <vasvlad@gmail.com> 0.8.4.2
  * Fixed problem with refreshing weather forecast
* Fri Jan 17 2014  Vlad Vasilyeu <vasvlad@gmail.com> 0.8.4.1
  * First release SailfishOS
# << files


