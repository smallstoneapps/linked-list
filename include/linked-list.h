#pragma once


#include <pebble.h>


typedef struct LinkedRoot LinkedRoot;
typedef bool (*ObjectCompare)(void* object1, void* object2);
typedef bool (*LinkedListForEachCallback)(void *object, void *context);


// Create a new LinkedRoot object, upon which all other linked list operations
// are performed.
LinkedRoot* linked_list_create_root(void);

// Returns the number of items currently in a linked list.
uint16_t linked_list_count(LinkedRoot* root);

// Adds a new item to the end of the linked list.
// This function does not copy the memory for the object, so you should ensure
// that the object does not get destroyed.
void linked_list_append(LinkedRoot* root, void* object);

// Adds a new item to the front of the linked list.
// This function does not copy the memory for the object, so you should ensure
// that the object does not get destroyed.
void linked_list_prepend(LinkedRoot* root, void* object);

// Adds a new item after the specified position in the linked list.
// This function does not copy the memory for the object, so you should ensure
// that the object does not get destroyed.
void linked_list_insert(LinkedRoot* root, void* object, uint16_t after);

// Returns the object at the specified position in the linked list.
void* linked_list_get(LinkedRoot* root, uint16_t index);

// Removes the object at the specified position in the list.
// This does not free the memory for the object, you should take care of that
// yourself.
void linked_list_remove(LinkedRoot* root, uint16_t index);

// Removes all items in a list.
// This does not free the memory for the objects in the list, you should take
// care of that yourself.
void linked_list_clear(LinkedRoot* root);

// Returns true if the specified object is in the list, otherwise returns false.
// Compares the pointers so this will only work with the exact same object, but
// not a copy.
bool linked_list_contains(LinkedRoot* root, void* object);

// Returns true if the specified object is in the list, otherwise returns false.
// Uses the specified ObjectCompare function to compare objects.
bool linked_list_contains_compare(LinkedRoot* root, void* object, ObjectCompare compare);

// Returns the index of the specified object in the list. If the object can not
// be found, returns -1.
// Compares the pointers so this will only work with the exact same object, but
// not a copy.
int16_t linked_list_find(LinkedRoot* root, void* object);

// Returns the index of the specified object in the list. If the object can not
// be found, returns -1.
// Uses the specified ObjectCompare function to compare objects.
int16_t linked_list_find_compare(LinkedRoot* root, void* object, ObjectCompare compare);

// Iterates over the list. Stops iterating if the callback returns false.
void linked_list_foreach(LinkedRoot* root, LinkedListForEachCallback callback, void* context);
