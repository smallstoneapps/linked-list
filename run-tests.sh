# Linked List v0.0.1
# A Pebble library for working with linked lists.
# http://smallstoneapps.github.io/linked-list/

# ----------------------

# The MIT License (MIT)

# Copyright © 2014 Matthew Tole

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# --------------------

# run-tests.sh

# Compile and run the tests.
cd tests/
gcc \
  linked-list.c \
  ../src/linked-list.c \
  -I ~/pebble-dev/PebbleSDK-2/Pebble/include \
  -I . \
  -std=c11 \
  -o tests
./tests
rm tests
cd ..
printf "\x1B[0m"