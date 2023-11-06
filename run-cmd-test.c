/*
 * Cursus Command Run Test
 *
 * Copyright (c) 2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

#include <cursus/blob.h>
#include <cursus/ibuf-blob.h>
#include <cursus/ibuf-unix.h>
#include <cursus/obuf-blob.h>
#include <cursus/obuf-unix.h>
#include <cursus/process.h>

static int cmd_run_cb (void *cookie)
{
	int *f = cookie;

	close (f[0]); close (f[2]);  /* close pipe read ends */
	close (0); open ("/dev/null", O_RDONLY);
	close (1); dup (f[1]); close (f[1]);
	close (2); dup (f[3]); close (f[3]);
	return 1;
}

static int cmd_run_poll (int f[4], struct ibuf b[2], int timeout)
{
	struct pollfd p[2] = {{ .fd = f[0], .events = POLLIN },
			      { .fd = f[2], .events = POLLIN }};
	int n;

	close (f[1]); close (f[3]);  /* close pipe write ends */

	do {
		while ((n = poll (p, 2, timeout)) == -1 && errno == EINTR) {}

		if (n == -1)
			break;
	}
	while (ibuf_do_poll (b + 0, p + 0) | ibuf_do_poll (b + 1, p + 1));

	close (f[0]); close (f[2]);  /* close pipe read ends */
	return n;
}

int cmd_run (char *const argv[], struct blob res[2])
{
	struct ibuf b[2];
	pid_t c;
	int s, f[4];

	if (pipe (f + 0) == -1)
		goto no_stdout;

	if (pipe (f + 2) == -1)
		goto no_stderr;

	if (!ibuf_blob_init (b + 0, 32))
		goto no_stdout_blob;

	if (!ibuf_blob_init (b + 1, 32))
		goto no_stderr_blob;

	if ((c = process_spawn (argv, cmd_run_cb, f)) == -1)
		goto no_spawn;

	(void) cmd_run_poll (f, b, -1);

	s = process_wait (c);

	res[0].data = b[0].head; res[0].size = b[0].cursor - b[0].head;
	res[1].data = b[1].head; res[1].size = b[1].cursor - b[1].head;
	return s;
no_spawn:
	ibuf_fini (b + 1);
no_stderr_blob:
	ibuf_fini (b + 0);
no_stdout_blob:
	close (f[2]); close (f[3]);
no_stderr:
	close (f[0]); close (f[1]);
no_stdout:
	return 0;
}

int main (int argc, char *argv[])
{
	struct blob res[2];
	int s;

	s = cmd_run (argv + 1, res);

	fprintf (stderr, "N: status = %d\n", s);
	fprintf (stderr, "N: got %zu bytes on stdout\n", res[0].size);
	fprintf (stderr, "N: got %zu bytes on stderr\n", res[1].size);

	blob_fini (res + 0);
	blob_fini (res + 1);
	return 0;
}
