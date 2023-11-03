/*
 * Yonk I/O Input Buffer
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_IO_IBUF_H
#define YONK_IO_IBUF_H  1

#include <stdlib.h>

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

#endif  /* YONK_IO_IBUF_H */
