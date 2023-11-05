/*
 * Cursus I/O Blob
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CURSUS_BLOB_H
#define CURSUS_BLOB_H  1

#include <stdlib.h>
#include <string.h>

struct blob {
	void  *data;
	size_t size;
};

static inline int blob_init (struct blob *o, size_t size, int zero)
{
	o->data = zero ? calloc (1, size) : malloc (size);
	o->size = size;
	return o->data != NULL;
}

static inline void blob_fini (struct blob *o)
{
	free (o->data);
}

static inline void blob_set_string (struct blob *o, const char *s)
{
	o->data = (void *) s;
	o->size = strlen (s);
}

#endif  /* CURSUS_BLOB_H */
