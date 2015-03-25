Name:       org.tizen.ui_controls
Summary:    UI Controls (Elementary)
Version:    1.0.0
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
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

%define prefix "/opt/usr/apps/org.tizen.ui_controls"

%build
rm -rf CMakeFiles CMakeCache.txt && cmake . -DCMAKE_INSTALL_PREFIX=%{prefix}
make %{?jobs:-j%jobs}

%install
%make_install

mkdir -p %{buildroot}/%{_datadir}/packages/
cp %{_builddir}/%{buildsubdir}/org.tizen.ui_controls.xml %{buildroot}/%{_datadir}/packages/org.tizen.ui_controls.xml

mkdir -p %{buildroot}/%{_datadir}/license
cp %{_builddir}/%{buildsubdir}/LICENSE %{buildroot}/%{_datadir}/license/%{name}

%files
%defattr(-,root,root,-)
/opt/usr/apps/org.tizen.ui_controls/bin/*
/opt/usr/apps/org.tizen.ui_controls/res/*
%{_datadir}/packages/org.tizen.ui_controls.xml
%{_datadir}/license/%{name}
%manifest %{name}.manifest
