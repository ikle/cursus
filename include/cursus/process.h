/*
 * Cursus Process Spawn Helpers
 *
 * Copyright (c) 2020-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CURSUS_PROCESS_H
#define CURSUS_PROCESS_H  1

#include <sys/types.h>

/*
 * Optional pre-exec callback to redirect files and lower process rights.
 * Should return zero on error to prevent exec.
 */
typedef int process_cb (void *cookie);

pid_t process_spawn (char *const argv[], process_cb cb, void *cookie);
int   process_wait  (pid_t pid);

#endif  /* CURSUS_PROCESS_H */
