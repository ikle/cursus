/*
 * Yonk I/O Input Buffer
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_IO_IBUF_H
#define YONK_IO_IBUF_H  1

#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct ibuf;

typedef int ibuf_cb (struct ibuf *o, int count);

struct ibuf {
	char *head, *cursor, *tail;
	ibuf_cb *cb;
};

static inline int ibuf_init (struct ibuf *o, size_t size, ibuf_cb cb)
{
	if ((o->head = malloc (size)) == NULL)
		return 0;

	o->cursor = o->head;
	o->tail   = o->head + size;
	o->cb     = cb;
	return 1;
}

static inline void ibuf_fini (struct ibuf *o)
{
	free (o->head);
}

#ifndef MIN
#define MIN(x, y)  (((x) < (y)) ? (x) : (y))
#endif

static inline int ibuf_push (struct ibuf *o, const void *data, size_t count)
{
	count = MIN (MIN (count, INT_MAX), o->tail - o->cursor);

	memcpy (o->cursor, data, count);

	o->cursor += count;
	return o->cb (o, count);
}

#endif  /* YONK_IO_IBUF_H */
