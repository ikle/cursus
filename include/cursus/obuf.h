/*
 * Cursus I/O Output Buffer
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CURSUS_OBUF_H
#define CURSUS_OBUF_H  1

#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct obuf;

typedef int obuf_cb (struct obuf *o, int count);

struct obuf {
	char *head, *cursor, *tail;
	obuf_cb *cb;
};

static inline int obuf_init (struct obuf *o, size_t size, obuf_cb cb)
{
	if ((o->head = malloc (size)) == NULL)
		return 0;

	o->tail   = o->head + size;
	o->cursor = o->tail;
	o->cb     = cb;
	return 1;
}

static inline void obuf_fini (struct ibuf *o)
{
	free (o->head);
}

#ifndef MIN
#define MIN(x, y)  (((x) < (y)) ? (x) : (y))
#endif

static inline int obuf_pull (struct obuf *o, void *data, size_t count)
{
	count = MIN (MIN (count, INT_MAX), o->tail - o->cursor);

	memcpy (data, o->cursor, count);

	o->cursor += count;
	return o->cb (o, count);
}

#endif  /* CURSUS_OBUF_H */
