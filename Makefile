CC=gcc
CFLAGS=-std=c11
CINCLUDES=-I tests/include/ -I tests/

test: buildtest
	tests/run
	rm tests/run
	printf "\x1B[0m"

buildtest:
	$(CC) $(CFLAGS) $(CINCLUDES) tests/linked-list.c src/linked-list.c -o tests/run