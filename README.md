# Linked List [![Build Status](http://img.shields.io/travis/smallstoneapps/linked-list.svg?style=flat-square)](https://travis-ci.org/smallstoneapps/linked-list/)&nbsp;[![npm (scoped)](https://img.shields.io/npm/v/@smallstoneapps/linked-list.svg?maxAge=2592000&style=flat-square)](https://www.npmjs.com/package/@smallstoneapps/linked-list)&nbsp;[![MIT License](http://img.shields.io/badge/license-MIT-lightgray.svg?style=flat-square)](./LICENSE)

A simple linked list implementation for Pebble apps and watchfaces.

## Installation

*You must be using Pebble SDK 3.12 or newer to use this library.*

To install the package to your app, use the pebble tool:

```
pebble package install @smallstoneapps/linked-list
```

## Usage

```c
// This is not a complete example, but should demonstrate the basic usage of
// the Linked List library.

#include <@smallstoneapps/linked-list/linked-list.h>

LinkedRoot* root;

static void init(void) {
  root = linked_list_create_root();
  linked_list_append(root, data);
  printf("%d", linked_list_count(root));
}

static void deinit(void) {
  linked_list_clear(root);
  destroy(root);
}
```

## Tests

Unit tests for Data Processor exist in the `tests` folder.

To run the tests:

```sh
make test
```
