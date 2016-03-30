#include <stdio.h>
#include <stdlib.h>

#include "vcl.h"
#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"

#include <jemalloc/jemalloc.h>

void
vjemalloc_log_cb(void *vctx, const char *msg)
{
	const struct vrt_ctx *ctx = (struct vrt_ctx*)vctx;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

	VSLb(ctx->vsl, SLT_VCL_Log, "%s", msg);
}

void
vjemalloc_write_cb(void *vvsb, const char *msg)
{
	struct vsb *v = (struct vsb*)vvsb;

	CHECK_OBJ_NOTNULL(v, VSB_MAGIC);

	VSB_cat(v, msg);
}

VCL_VOID
vmod_print_stats(VRT_CTX)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	
	malloc_stats_print(&vjemalloc_log_cb, (void*)ctx, NULL);
}

VCL_STRING
vmod_get_stats(VRT_CTX)
{
	struct vsb *v;
	unsigned available;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

	available = WS_Reserve(ctx->ws, 0);

	v = VSB_new(NULL, ctx->ws->f, available, VSB_AUTOEXTEND);

	CHECK_OBJ_NOTNULL(v, VSB_MAGIC);

	malloc_stats_print(&vjemalloc_write_cb, (void*)v, NULL);

	VSB_finish(v);

	if (VSB_error(v) || VSB_len(v) + 1 > available) {
	    VSLb(ctx->vsl, SLT_Error, "VSB error when writing jemalloc stats");
	    
	    WS_Release(ctx->ws, 0);

	    return "ERROR";
	}

	WS_Release(ctx->ws, VSB_len(v) + 1);

	return (v->s_buf);
}
