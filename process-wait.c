/*
 * Cursus Process Wait
 *
 * Copyright (c) 2020-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <sys/wait.h>

#include <cursus/process.h>

int process_wait (pid_t pid)
{
	pid_t c;
	int s;

	for (;;) {
		while ((c = waitpid (pid, &s, 0)) == -1 && errno == EINTR) {}

		if (c == -1)
			return -1;

		if (WIFEXITED (s))
			return WEXITSTATUS (s);

		if (WIFSIGNALED (s))
			return 128 + WTERMSIG (s);
	}
}
