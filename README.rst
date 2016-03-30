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

                print_stats(STRING options = "")
Return value
	VOID
Description
	Prints jemalloc stats to varnishlog. Supports optional jemalloc print options.
Example
        ::

                jemalloc.print_stats(STRING options = "");

get_stats
---------

Prototype
        ::

                get_stats()
Return value
	STRING
Description
	Gets jemalloc stats as a STRING (not header safe, requires ~50k workspace). Supports
	optional jemalloc print options.
Example
        ::

                synthetic(jemalloc.get_stats(options = "a"));

USAGE EXAMPLE
=============

In your VCL you could then use this vmod along the following lines::

        import jemalloc;

	sub vcl_recv {
		if(req.url == "/jemalloc") {
			return (synth(200, "JEMALLOC"));
		}
	}

	sub vcl_synth {
		set resp.http.Content-Type = "text/plain; charset=utf-8";
		synthetic(jemalloc.get_stats(options = "a"));
		return (deliver);
	}

        sub vcl_deliver {
		if (req.http.jemalloc) {
			jemalloc.print_stats();
		}
        }

