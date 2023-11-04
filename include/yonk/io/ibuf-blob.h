/*
 * Yonk I/O Blob Input Buffer
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_IO_IBUF_BLOB_H
#define YONK_IO_IBUF_BLOB_H  1

#include <errno.h>

#include <yonk/io/ibuf.h>

static inline int ibuf_blob_cb (struct ibuf *o, int count)
{
	size_t size = o->tail - o->head;
	size_t next = size * 2;
	void *p;

	if (count <= 0)
		return 0;

	if (o->tail > o->cursor)
		return 1;

	if (next < size || (p = realloc (o->head, next)) == NULL) {
		errno = ENOMEM;
		return 0;
	}

	o->tail   = p + next;
	o->cursor = p + (o->cursor - o->head);
	o->head   = p;
	return 1;
}

static inline int ibuf_blob_init (struct ibuf *o, size_t size)
{
	return ibuf_init (o, size, ibuf_blob_cb);
}

static inline void ibuf_blob_fini (struct ibuf *o)
{
	ibuf_fini (o);
}

#endif  /* YONK_IO_IBUF_BLOB_H */
