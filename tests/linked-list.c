/*

Linked List v0.0.1
A Pebble library for working with linked lists.
http://smallstoneapps.github.io/linked-list/

----------------------

The MIT License (MIT)

Copyright © 2014 Matthew Tole

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

--------------------

tests/linked-list.c

*/

#include "unit.h"
#include <pebble.h>
#include "../src/linked-list.h"

// Colour code definitions to make the output all pretty.
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// Keep track of how many tests have run, and how many have passed.
int tests_run = 0;
int tests_passed = 0;
const int NUM_TESTS = 17;

typedef struct Object {
  uint8_t id;
} Object;

LinkedRoot* root = NULL;

static void before_each(void) {
  root = linked_list_create_root();
  // persist_clear();
}

static void after_each(void) {
}

static Object* create_object(uint16_t id) {
  Object* object = malloc(sizeof(Object));
  object->id = id;
  return object;
}

static uint8_t get_id(void* obj) {
  return ((Object*)obj)->id;
}

/*static char* test_exists_fail(void) {
  bool pass = (false == persist_exists(0));
  mu_assert(pass, "Something exists when it shouldn't.");
  return 0;
}
*/

static char* count_empty(void) {
  mu_assert(0 == linked_list_count(root), "List is not empty.");
  return 0;
}

static char* get_invalid_index(void) {
  mu_assert(NULL == linked_list_get(root, 0), "Get invalid index does not return NULL");
  return 0;
}

static char* append_count_single(void) {
  linked_list_append(root, create_object(1));
  mu_assert(1 == linked_list_count(root), "Appending one item doesn't set size to 1.");
  return 0;
}

static char* append_count_multiple(void) {
  linked_list_append(root, create_object(1));
  linked_list_append(root, create_object(2));
  linked_list_append(root, create_object(3));
  linked_list_append(root, create_object(4));
  mu_assert(4 == linked_list_count(root), "Appending four item doesn't set size to 4.");
  return 0;
}

static char* append_get_single(void) {
  linked_list_append(root, create_object(1));
  Object* object = (Object*)linked_list_get(root, 0);
  mu_assert(NULL != object && 1 == object->id, "Cannot get single appended item.");
  return 0;
}

static char* append_get_multiple(void) {
  linked_list_append(root, create_object(1));
  linked_list_append(root, create_object(2));
  Object* object1 = (Object*)linked_list_get(root, 0);
  Object* object2 = (Object*)linked_list_get(root, 1);
  mu_assert(NULL != object1 && 1 == object1->id, "Cannot get first appended item.");
  mu_assert(NULL != object2 && 2 == object2->id, "Cannot get second appended item.");
  return 0;
}

static char* prepend_empty(void) {
  linked_list_prepend(root, create_object(1));
  Object* object = (Object*)linked_list_get(root, 0);
  mu_assert(NULL != object && 1 == object->id, "Cannot get item prepended on empty list.");
  return 0;
}

static char* prepend_not_empty(void) {
  linked_list_append(root, create_object(1));
  linked_list_prepend(root, create_object(2));
  Object* object = (Object*)linked_list_get(root, 0);
  mu_assert(NULL != object && 2 == object->id, "Cannot get item prepended on list.");
  return 0;
}

static char* insert_empty(void) {
  linked_list_insert(root, create_object(1), 1);
  Object* object = (Object*)linked_list_get(root, 0);
  mu_assert(NULL != object && 1 == object->id, "Cannot insert item on empty list.");
  return 0;
}

static char* insert_valid_index(void) {
  linked_list_append(root, create_object(1));
  linked_list_append(root, create_object(2));
  linked_list_insert(root, create_object(3), 0);
  Object* object = (Object*)linked_list_get(root, 1);
  mu_assert(NULL != object && 3 == object->id, "Cannot insert item at a valid index.");
  return 0;
}

static char* insert_invalid_index(void) {
  linked_list_append(root, create_object(1));
  linked_list_append(root, create_object(2));
  linked_list_insert(root, create_object(3), 4);
  Object* object = (Object*)linked_list_get(root, 2);
  mu_assert(NULL != object && 3 == object->id, "Cannot insert item at an invalid index.");
  return 0;
}

static char* remove_only_item(void) {
  linked_list_append(root, create_object(1));
  linked_list_remove(root, 0);
  mu_assert(0 == linked_list_count(root), "Removing only item failed.");
  return 0;
}

static char* remove_single_item(void) {
  linked_list_append(root, create_object(1));
  linked_list_append(root, create_object(2));
  linked_list_append(root, create_object(3));
  linked_list_remove(root, 1);
  mu_assert(1 == get_id(linked_list_get(root, 0)), "Removing single item failed.");
  mu_assert(3 == get_id(linked_list_get(root, 1)), "Removing single item failed.");
  mu_assert(2 == linked_list_count(root), "Removing single item failed.");
  return 0;
}

static char* remove_multiple_items(void) {
  linked_list_append(root, create_object(1));
  linked_list_append(root, create_object(2));
  linked_list_append(root, create_object(3));
  linked_list_remove(root, 2);
  linked_list_remove(root, 1);
  mu_assert(1 == get_id(linked_list_get(root, 0)), "Removing multiple items failed.");
  mu_assert(1 == linked_list_count(root), "Removing multiple items failed.");
  return 0;
}

static char* clear_empty(void) {
  linked_list_clear(root);
  mu_assert(0 == linked_list_count(root), "List is not empty after clearing empty list.");
  return 0;
}

static char* clear_single(void) {
  linked_list_append(root, create_object(1));
  linked_list_clear(root);
  mu_assert(0 == linked_list_count(root), "List is not empty after clearing single item list.");
  return 0;
}

static char* clear_multiple(void) {
  linked_list_append(root, create_object(1));
  linked_list_append(root, create_object(2));
  linked_list_append(root, create_object(3));
  linked_list_clear(root);
  mu_assert(0 == linked_list_count(root), "List is not empty after clearing multiple item list.");
  return 0;
}

static char* all_tests(void) {
  mu_run_test(count_empty);
  mu_run_test(get_invalid_index);
  mu_run_test(append_count_single);
  mu_run_test(append_count_multiple);
  mu_run_test(append_get_single);
  mu_run_test(append_get_multiple);
  mu_run_test(prepend_empty);
  mu_run_test(prepend_not_empty);
  mu_run_test(insert_empty);
  mu_run_test(insert_valid_index);
  mu_run_test(insert_invalid_index);
  mu_run_test(remove_only_item);
  mu_run_test(remove_single_item);
  mu_run_test(remove_multiple_items);
  mu_run_test(clear_empty);
  mu_run_test(clear_single);
  mu_run_test(clear_multiple);
  return 0;
}

int main(int argc, char **argv) {
  printf("%s-------------------------\n", KCYN);
  printf("Running Linked List Tests\n");
  printf("-------------------------\n%s", KNRM);
  char* result = all_tests();
  if (0 != result) {
    printf("%sFailed Test:%s %s\n", KRED, KNRM, result);
  }
  printf("Tests Run: %s%d / %d%s\n", (tests_run >= NUM_TESTS) ? KGRN : KRED, tests_run, NUM_TESTS, KNRM);
  printf("Tests Passed: %s%d / %d%s\n", (tests_passed >= NUM_TESTS) ? KGRN : KRED, tests_passed, NUM_TESTS, KNRM);

  printf("%s----------------------------%s\n", KCYN, KNRM);
  return result != 0;
}