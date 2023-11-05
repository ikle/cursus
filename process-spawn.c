/*
 * Cursus Process Spawn
 *
 * Copyright (c) 2020-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <unistd.h>

#include <cursus/process.h>

pid_t process_spawn (char *const argv[], process_cb cb, void *cookie)
{
	pid_t pid;

	if ((pid = fork ()) != 0)
		return pid;

	if (cb == NULL || cb (cookie))
		(void) execvp (argv[0], argv);

	_exit (127);
}
