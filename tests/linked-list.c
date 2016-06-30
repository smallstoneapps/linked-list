#include <pebble.h>
#include "unit.h"
#include "linked-list.h"

#define VERSION_LABEL "1.3.0"

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

typedef struct Object {
  uint8_t id;
} Object;

LinkedRoot* root = NULL;

static void before_each(void) {
  root = linked_list_create_root();
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

static bool object_compare(void* obj1, void* obj2) {
  return ((Object*)obj1)->id == ((Object*)obj2)->id;
}

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

static char* contains_true(void) {
  Object* object = create_object(1);
  linked_list_append(root, object);
  mu_assert(true == linked_list_contains(root, object), "Could not find object.");
  return 0;
}

static char* contains_false(void) {
  Object* object = create_object(1);
  mu_assert(false == linked_list_contains(root, object), "Found object that it should not.");
  return 0;
}

static char* contains_compare_true(void) {
  Object* object1 = create_object(1);
  Object* object2 = create_object(1);
  linked_list_append(root, object1);
  mu_assert(true == linked_list_contains_compare(root, object2, object_compare), "Could not find object with compare.");
  return 0;
}

static char* contains_compare_false(void) {
  Object* object1 = create_object(1);
  Object* object2 = create_object(2);
  linked_list_append(root, object1);
  mu_assert(false == linked_list_contains_compare(root, object2, object_compare), "Found invalid object with compare.");
  return 0;
}

static char* find_valid(void) {
  Object* object = create_object(1);
  linked_list_append(root, object);
  mu_assert(0 == linked_list_find(root, object), "Could not find object index.");
  return 0;
}

static char* find_invalid(void) {
  Object* object = create_object(1);
  mu_assert(-1 == linked_list_find(root, object), "Found index for unknown object.");
  return 0;
}

static char* find_compare_valid(void) {
  Object* object1 = create_object(1);
  Object* object2 = create_object(1);
  linked_list_append(root, object1);
  mu_assert(0 == linked_list_find_compare(root, object2, object_compare), "Could not find object index by comparison.");
  return 0;
}

static char* find_compare_invalid(void) {
  Object* object1 = create_object(1);
  Object* object2 = create_object(2);
  linked_list_append(root, object1);
  mu_assert(-1 == linked_list_find_compare(root, object2, object_compare), "Found incorrect object index by comparison.");
  return 0;
}

static uint8_t foreach_counter = 0;

static bool foreach_callback(void *object, void *context) {
  foreach_counter += 1;
  if (context == NULL) {
    return true;
  }
  return false;
}

static char* foreach(void) {
  foreach_counter = 0;
  Object* object1 = create_object(1);
  Object* object2 = create_object(2);
  linked_list_append(root, object1);
  linked_list_append(root, object2);
  linked_list_foreach(root, foreach_callback, NULL);
  mu_assert(foreach_counter == 2, "Did not loop through every item in the list");
  return 0;
}

static char* foreach_bail(void) {
  foreach_counter = 0;
  Object* object1 = create_object(1);
  Object* object2 = create_object(2);
  linked_list_append(root, object1);
  linked_list_append(root, object2);
  linked_list_foreach(root, foreach_callback, object1);
  mu_assert(foreach_counter == 1, "Did not bail out of the loop");
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
  mu_run_test(contains_true);
  mu_run_test(contains_false);
  mu_run_test(contains_compare_true);
  mu_run_test(contains_compare_false);
  mu_run_test(find_valid);
  mu_run_test(find_invalid);
  mu_run_test(find_compare_valid);
  mu_run_test(find_compare_invalid);
  mu_run_test(foreach);
  mu_run_test(foreach_bail);
  return 0;
}

// Test application entry point.
// Executes all the tests and prints the results in pretty colours.
int main(int argc, char **argv) {
  printf("%s---------------------------------\n", KCYN);
  printf("| Running Linked List %s Tests |\n", VERSION_LABEL);
  printf("---------------------------------\n%s", KNRM);
  char* result = all_tests();
  if (0 != result) {
    printf("%s- Failed Test:%s %s\n", KRED, KNRM, result);
  }
  printf("- Tests Run: %s%d%s\n", (tests_run == tests_passed) ? KGRN : KRED, tests_run, KNRM);
  printf("- Tests Passed: %s%d%s\n", (tests_run == tests_passed) ? KGRN : KRED, tests_passed, KNRM);

  printf("%s---------------------------------%s\n", KCYN, KNRM);
  return result != 0;
}
