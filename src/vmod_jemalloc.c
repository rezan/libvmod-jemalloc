#include <stdio.h>
#include <stdlib.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"

#include <jemalloc/jemalloc.h>

#define VSB_MAGIC		0x4a82dd8a

void
vjemalloc_log_cb(void *vsp, const char *msg)
{
	struct sess *sp = (struct sess*)vsp;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);

	WSP(sp, SLT_VCL_Log, "%s", msg);
}

void
vjemalloc_write_cb(void *vvsb, const char *msg)
{
	struct vsb *v = (struct vsb*)vvsb;

	assert(v->s_magic == VSB_MAGIC);

	VSB_cat(v, msg);
}

void
vmod_print_stats(struct sess *sp, const char *options)
{
	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	
	malloc_stats_print(&vjemalloc_log_cb, (void*)sp, options);
}

const char *
vmod_get_stats(struct sess *sp, const char *options)
{
	struct vsb *v;
	unsigned available;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);

	available = WS_Reserve(sp->wrk->ws, 0);

	v = VSB_new(NULL, sp->wrk->ws->f, available, VSB_AUTOEXTEND);

	assert(v->s_magic == VSB_MAGIC);

	malloc_stats_print(&vjemalloc_write_cb, (void*)v, options);

	VSB_finish(v);

	if (VSB_error(v) || VSB_len(v) + 1 > available) {
	    WSP(sp, SLT_Error, "VSB error when writing jemalloc stats");
	    
	    WS_Release(sp->wrk->ws, 0);

	    return "ERROR (need more workspace)";
	}

	WS_Release(sp->wrk->ws, VSB_len(v) + 1);

	return (v->s_buf);
}
