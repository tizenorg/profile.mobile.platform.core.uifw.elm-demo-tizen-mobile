Name:       org.tizen.ui-controls
Summary:    UI Controls (Elementary)
Version:    1.0.3
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-system-system-settings)
BuildRequires:  pkgconfig(capi-appfw-app-manager)
BuildRequires:  app-core-efl-devel
BuildRequires:  efl-extension-devel
BuildRequires:  cmake
BuildRequires:  edje-bin
BuildRequires:  gettext-tools

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

mkdir -p %{buildroot}/%{_datadir}/packages/
cp %{_builddir}/%{buildsubdir}/org.tizen.ui-controls.xml %{buildroot}/%{_datadir}/packages/org.tizen.ui-controls.xml

mkdir -p %{buildroot}/%{_datadir}/license
cp %{_builddir}/%{buildsubdir}/LICENSE %{buildroot}/%{_datadir}/license/%{name}

%files
%defattr(-,root,root,-)
/opt/usr/apps/org.tizen.ui-controls/bin/*
/opt/usr/apps/org.tizen.ui-controls/res/*
/opt/usr/apps/org.tizen.ui-controls/res/locale/*/LC_MESSAGES/*
%{_datadir}/packages/org.tizen.ui-controls.xml
%{_datadir}/icons/default/small/org.tizen.ui-controls.png
%{_datadir}/license/%{name}
%manifest %{name}.manifest
