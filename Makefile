#
# Linked List v0.4
# A Pebble library for working with linked lists.
# http://smallstoneapps.github.io/linked-list/
#
# ----------------------
#
# The MIT License (MIT)
#
# Copyright © 2014 Matthew Tole
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# --------------------
#
# Makefile
#

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
CINCLUDES=-I $(PEBBLE_HEADERS) -I tests/

TEST_FILES=tests/linked-list.c
SRC_FILES=src/linked-list.c
TEST_EXTRAS=

all: test

test:
	@$(CC) $(CFLAGS) $(CINCLUDES) $(TEST_FILES) $(SRC_FILES) $(TEST_EXTRAS) -o tests/run
	@tests/run
	@rm tests/run
	@printf "\x1B[0m"

dist:
	@mkdir -p dist
	@mkdir -p tmp
	@$(CC) -c $(CFLAGS) $(CINCLUDES) $(SRC_FILES) -o tmp/linked-list.o
	@$(AR) rcs dist/liblinked-list.a tmp/linked-list.o
	@rm -r tmp
	@cp src/linked-list.h dist/linked-list.h