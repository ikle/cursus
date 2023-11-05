/*
 * Cursus I/O Poll Test
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>

#include <cursus/ibuf-blob.h>
#include <cursus/ibuf-unix.h>
#include <cursus/obuf-blob.h>
#include <cursus/obuf-unix.h>

static int do_poll (struct obuf *b0, struct ibuf *b1, int timeout)
{
	struct pollfd f[2] = {{ .fd = 1, .events = POLLOUT },
			      { .fd = 0, .events = POLLIN  }};
	int n;

	do {
		while ((n = poll (f, 2, timeout)) == -1 && errno == EINTR) {}

		if (n == -1)
			return n;
	}
	while (obuf_do_poll (b0, f + 0) | ibuf_do_poll (b1, f + 1));

	return 0;
}

int main (int argc, char *argv[])
{
	static const char sample[] = "Test obuf-blob string\n";
	struct obuf b0;
	struct ibuf b1;

	obuf_blob_init (&b0, sample, sizeof (sample) - 1);

	if (!ibuf_blob_init (&b1, 32)) {
		perror ("E: cannot initialize ibuf");
		return 1;
	}

	do_poll (&b0, &b1, -1);

	printf ("I: Send %zu bytes\n", b0.cursor - b0.head);
	printf ("I: Recv %zu bytes\n", b1.cursor - b1.head);
	return 0;
}
