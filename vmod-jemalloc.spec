Summary: jemalloc VMOD for Varnish
Name: vmod-jemalloc
Version: 0.1
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: libvmod-jemalloc.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish >= 4.0.2
BuildRequires: make
BuildRequires: python-docutils
BuildRequires: varnish >= 4.0.2
BuildRequires: varnish-libs-devel >= 4.0.2

%description
jemalloc VMOD

%prep
%setup -n libvmod-jemalloc-trunk

%build
%configure --prefix=/usr/
%{__make} %{?_smp_mflags}
%{__make} %{?_smp_mflags} check

%install
[ %{buildroot} != "/" ] && %{__rm} -rf %{buildroot}
%{__make} install DESTDIR=%{buildroot}
mv %{buildroot}/usr/share/doc/lib%{name} %{buildroot}/usr/share/doc/%{name}


%clean
[ %{buildroot} != "/" ] && %{__rm} -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/varnis*/vmods/
%doc /usr/share/doc/%{name}/*
%{_mandir}/man?/*

%changelog
* Mon Mar 28 2016 Reza Naghibi <reza@varnish-software.com> - 0.1
- Initial version.
