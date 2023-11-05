/*
 * Cursus I/O Page Input Buffer
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CURSUS_IBUF_PAGE_H
#define CURSUS_IBUF_PAGE_H  1

#include <cursus/ibuf.h>

static inline int ibuf_page_cb (struct ibuf *o, int count)
{
	return count > 0 && o->tail > o->cursor;
}

static inline int ibuf_page_init (struct ibuf *o, size_t size)
{
	return ibuf_init (o, size, ibuf_page_cb);
}

static inline void ibuf_page_fini (struct ibuf *o)
{
	ibuf_fini (o);
}

#endif  /* CURSUS_IBUF_PAGE_H */
