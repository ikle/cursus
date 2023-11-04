/*
 * Yonk I/O Output Buffer, POSIX I/O
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_IO_OBUF_UNIX_H
#define YONK_IO_OBUF_UNIX_H  1

#include <unistd.h>
#include <yonk/io/obuf.h>

static inline int obuf_pull_file (struct obuf *o, int fd)
{
	ssize_t count = MIN (o->tail - o->cursor, INT_MAX);

	if ((count = write (fd, o->cursor, count)) > 0)
		o->cursor += count;

	return o->cb (o, count);
}

#endif  /* YONK_IO_OBUF_UNIX_H */
