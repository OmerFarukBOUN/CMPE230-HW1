#pragma once

#include <string.h>
#ifndef CMPE230HW1_HASHMAP_H
#define CMPE230HW1_HASHMAP_H

#endif //CMPE230HW1_HASHMAP_H


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
void add_new_element(HashMap hashMap, char * str, int value);
int getValue(HashMap, char *);