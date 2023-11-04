/*
 * Yonk I/O Input Buffer, POSIX I/O
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_IO_IBUF_UNIX_H
#define YONK_IO_IBUF_UNIX_H  1

#include <poll.h>
#include <unistd.h>

#include <yonk/io/ibuf.h>

static inline int ibuf_push_file (struct ibuf *o, int fd)
{
	ssize_t count = MIN (o->tail - o->cursor, INT_MAX);

	if ((count = read (fd, o->cursor, count)) > 0)
		o->cursor += count;

	return o->cb (o, count);
}

static inline int ibuf_do_poll (struct ibuf *o, struct pollfd *p)
{
	if ((p->revents | POLLIN) == 0 || ibuf_push_file (o, p->fd))
		return p->events;

	return p->events &= ~POLLIN;
}

#endif  /* YONK_IO_IBUF_UNIX_H */
