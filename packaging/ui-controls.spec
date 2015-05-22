Name:       org.tizen.ui-controls
Summary:    UI Controls (Elementary)
Version:    1.0.0
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
%if "%{?tizen_profile_name}" == "tv"
#Systemd for Tizen-TV
#FIXME: when TV's application merge from TV profile, must have remove.
Source2:        packaging/ui-controls.service
%endif
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-system-system-settings)
BuildRequires:  app-core-efl-devel
BuildRequires:  vconf-devel
BuildRequires:  efl-extension-devel
BuildRequires:  cmake
BuildRequires:  edje-bin

%description
UI Controls (Elementary)

%prep
%setup -q

%define prefix "/opt/usr/apps/org.tizen.ui-controls"

%build
rm -rf CMakeFiles CMakeCache.txt && cmake . -DCMAKE_INSTALL_PREFIX=%{prefix}
make %{?jobs:-j%jobs}

%install
%make_install

%if "%{?tizen_profile_name}" == "tv"
#Systemd for Tizen-TV
#FIXME: when TV's application merge from TV profile, must have remove.
mkdir -p %{buildroot}/usr/lib/systemd/system/basic.target.wants
install -m 0644 %SOURCE2 %{buildroot}/usr/lib/systemd/system
ln -s ../ui-controls.service %{buildroot}/usr/lib/systemd/system/basic.target.wants/ui-controls.service
%endif

mkdir -p %{buildroot}/%{_datadir}/packages/
cp %{_builddir}/%{buildsubdir}/org.tizen.ui-controls.xml %{buildroot}/%{_datadir}/packages/org.tizen.ui-controls.xml

mkdir -p %{buildroot}/%{_datadir}/license
cp %{_builddir}/%{buildsubdir}/LICENSE %{buildroot}/%{_datadir}/license/%{name}

%files
%defattr(-,root,root,-)
/opt/usr/apps/org.tizen.ui-controls/bin/*
/opt/usr/apps/org.tizen.ui-controls/res/*
%{_datadir}/packages/org.tizen.ui-controls.xml
%{_datadir}/icons/default/small/org.tizen.ui-controls.png
%{_datadir}/license/%{name}
%manifest %{name}.manifest
%if "%{?tizen_profile_name}" == "tv"
#Systemd for Tizen-TV
#FIXME: when TV's application merge from TV profile, must have remove.
%{_libdir}/systemd/system/ui-controls.service
%{_libdir}/systemd/system/basic.target.wants/ui-controls.service
%endif
