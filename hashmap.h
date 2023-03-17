#pragma once

#include <string.h>

typedef struct HashMapEntry {
    char *key;
    int value;
} HashMapEntry;

typedef struct HashMap {
    struct HashMapEntry *array;
    int fullness;
    int size;
} HashMap;

HashMap initializeHashMap(); // allocates hashmap's array
void add_new_element(HashMap *hashMap, char * key, int value); // adds new element to the given hashmap
int getValue(HashMap *, char *); // gets the value of given string