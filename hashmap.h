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

HashMap initializeHashMap();
void add_new_element(HashMap *hashMap, char * key, int value);
int getValue(HashMap *, char *);