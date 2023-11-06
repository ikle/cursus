/*
 * Cursus I/O Input Buffer, POSIX I/O
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CURSUS_IBUF_UNIX_H
#define CURSUS_IBUF_UNIX_H  1

#include <poll.h>
#include <unistd.h>

#include <cursus/ibuf.h>

static inline int ibuf_push_file (struct ibuf *o, int fd)
{
	ssize_t count = MIN (o->tail - o->cursor, INT_MAX);

	if ((count = read (fd, o->cursor, count)) > 0)
		o->cursor += count;

	return o->cb (o, count);
}

static inline int ibuf_do_poll (struct ibuf *o, struct pollfd *p)
{
	if ((p->revents & (POLLIN|POLLHUP)) == 0 || ibuf_push_file (o, p->fd))
		return p->events;

	return p->fd = -1, p->events &= ~POLLIN;
}

#endif  /* CURSUS_IBUF_UNIX_H */
