Summary: jemalloc VMOD for Varnish
Name: vmod-jemalloc
Version: 0.1-3.0
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: libvmod-example.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish > 3.0
BuildRequires: make
BuildRequires: python-docutils

%description
jemalloc VMOD

%prep
%setup -n libvmod-jemalloc

%build
# this assumes that VARNISHSRC is defined on the rpmbuild command line, like this:
# rpmbuild -bb --define 'VARNISHSRC /home/user/rpmbuild/BUILD/varnish-3.0.3' redhat/*spec
./configure VARNISHSRC=%{VARNISHSRC} VMODDIR="$(PKG_CONFIG_PATH=%{VARNISHSRC} pkg-config --variable=vmoddir varnishapi)" --prefix=/usr/ --docdir='${datarootdir}/doc/%{name}'
make
make check

%install
make install DESTDIR=%{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/varnis*/vmods/
%doc /usr/share/doc/%{name}/*
%{_mandir}/man?/*

%changelog
* Fri Apr 29 2016 Reza Naghibi <reza@varnish-software.com> - 0.1-3.0
- Initial version.
