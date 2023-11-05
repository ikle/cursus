/*
 * Cursus I/O Blob Output Buffer
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CURSUS_OBUF_BLOB_H
#define CURSUS_OBUF_BLOB_H  1

#include <cursus/obuf.h>

static inline int obuf_blob_cb (struct obuf *o, int count)
{
	return count > 0 && o->tail > o->cursor;
}

static inline int obuf_blob_init (struct obuf *o, const void *data, size_t size)
{
	o->head   = (void *) data;
	o->cursor = o->head;
	o->tail   = o->head + size;
	o->cb     = obuf_blob_cb;
	return 1;
}

static inline void obuf_blob_fini (struct obuf *o)
{
	/* nothing */
}

#endif  /* CURSUS_OBUF_BLOB_H */
