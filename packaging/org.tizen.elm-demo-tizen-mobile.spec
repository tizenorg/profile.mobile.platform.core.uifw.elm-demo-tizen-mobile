%define PREFIX /usr/apps/org.tizen.elm-demo-tizen-mobile
Name: org.tizen.elm-demo-tizen-mobile
Version:    0.1
Release:    1
Summary: Tizen TV theme demo
Source: %{name}-%{version}.tar.gz
License: Apache License, Version 2.0
Group: tizen/Application
BuildRequires: automake
BuildRequires: libtool
BuildRequires: pkgconfig(elementary)
BuildRequires: edje-bin
BuildRequires: embryo
BuildRequires: embryo-bin
BuildRequires: pkgconfig(appcore-efl)
BuildRequires: pkgconfig(efl-extension)

%description
Tizen TV theme demo

%prep
%setup -q

%build
libtoolize
autoreconf -ivf
./configure --prefix=/usr/apps/org.tizen.elm-demo-tizen-mobile
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files -n org.tizen.elm-demo-tizen-mobile
%defattr(-,root,root,-)
/usr/apps/org.tizen.elm-demo-tizen-mobile/bin/elm_demo_tizen_mobile
/usr/apps/org.tizen.elm-demo-tizen-mobile/data/
/usr/apps/org.tizen.elm-demo-tizen-mobile/data/images/*
/usr/apps/org.tizen.elm-demo-tizen-mobile/data/edc/layout.edj
/usr/apps/org.tizen.elm-demo-tizen-mobile/data/edc/button.edj
/usr/share/packages/org.tizen.elm-demo-tizen-mobile.xml
