/*
 * Cursus I/O Output Buffer, POSIX I/O
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CURSUS_OBUF_UNIX_H
#define CURSUS_OBUF_UNIX_H  1

#include <poll.h>
#include <unistd.h>

#include <cursus/obuf.h>

static inline int obuf_pull_file (struct obuf *o, int fd)
{
	ssize_t count = MIN (o->tail - o->cursor, INT_MAX);

	if ((count = write (fd, o->cursor, count)) > 0)
		o->cursor += count;

	return o->cb (o, count);
}

static inline int obuf_do_poll (struct obuf *o, struct pollfd *p)
{
	if ((p->revents | POLLOUT) == 0 || obuf_pull_file (o, p->fd))
		return p->events;

	return p->events &= ~POLLOUT;
}

#endif  /* CURSUS_OBUF_UNIX_H */
