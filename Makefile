DESCRIPTION = Process Management and I/O Library
URL = https://github.com/ikle/cursus

LIBNAME	= cursus
LIBVER	= 0
LIBREV	= 0.14

include make-core.mk

.PHONY: test

test: build-tests
	echo 01234567890123456789 | ./poll-0-test
	echo 0123456789012345678901234567890123456789012345 | ./poll-0-test
	./run-cmd-test
	./run-cmd-test lsz -lR
	./run-cmd-test ls -lR
	./run-cmd-test ls lR
	./run-cmd-test ls -lR . tzz
