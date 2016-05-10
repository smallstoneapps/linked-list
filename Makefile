PEBBLE_HEADERS=tests/include

CC=gcc
ifeq ($(TRAVIS), true)
CC_TEST=$(CC)
CFLAGS=
AR=ar
else
CC_TEST=arm-none-eabi-gcc
CFLAGS=-std=c11
AR=arm-none-eabi-ar
endif
CINCLUDES=-I $(PEBBLE_HEADERS) -I tests/ -I include/

TEST_FILES=tests/linked-list.c
SRC_FILES=src/c/linked-list.c
TEST_EXTRAS=

all: test

test:
	@$(CC) $(CFLAGS) $(CINCLUDES) $(TEST_FILES) $(SRC_FILES) $(TEST_EXTRAS) -o tests/run
	@tests/run
	@rm tests/run
	@printf "\x1B[0m"
