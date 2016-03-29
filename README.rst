============
vmod_jemalloc
============

----------------------
Varnish jemalloc VMOD
----------------------

:Date: 2016-03-29
:Version: 1.0
:Manual section: 3

SYNOPSIS
========

import jemalloc;

DESCRIPTION
===========

Get internal jemalloc statistics

FUNCTIONS
=========

print_stats
-----------

Prototype
        ::

                print_stats()
Return value
	VOID
Description
	prints jemalloc stats to varnishlog
Example
        ::

                jemalloc.print_stats();

get_stats
---------

Prototype
        ::

                get_stats()
Return value
	STRING
Description
	gets jemalloc stats as a STRING (not header safe, requires ~20k workspace)
Example
        ::

                synthetic(jemalloc.get_stats());

USAGE EXAMPLE
=============

In your VCL you could then use this vmod along the following lines::

        import jemalloc;

        sub vcl_deliver {
		if (req.http.jemalloc) {
			jemalloc.print_stats();
		}
        }

