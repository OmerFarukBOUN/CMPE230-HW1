#include "standart.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashmap_min_size 10
#define max_load 0.5f
#define size_factor 2

int doubleHash(char *, HashMap *);
void biggerarray(HashMap *hashMap, int newSize);
void add_new_element(HashMap* hashMap, char *key, int value);


HashMap initializeHashMap() {
    HashMap a;
    a.array = (HashMapEntry *) calloc(hashmap_min_size, sizeof(HashMapEntry));
    a.fullness = 0;
    a.size = hashmap_min_size;
    return a;
}

int hash(char *str, int size) {
    int hash = 0;
    int i = 0;
    while (str[i] != 0) {
        hash = ((hash << 3) + str[i] - 'a' + 1) % size;
        i++;
    }
    return hash;
}

int doubleHash(char *str, HashMap *hashMap) {
    int i = 0;
    int firstHash = hash(str, (*hashMap).size);
    while (1) {
        if ((*hashMap).array[(firstHash + i) * (i + 1)].key == 0 || (strcmp((*hashMap).array[(firstHash + i) * (i + 1)].key, str)) == 0) {
            return (firstHash + i) * (i + 1);
        } else {
            i++;
        }
    }
}

void biggerarray(HashMap *hashMap, int newSize) {
    HashMapEntry *oldarray = (*hashMap).array;
    int oldsize = (*hashMap).size;
    (*hashMap).array = (struct HashMapEntry *) calloc(newSize, sizeof(HashMapEntry));
    (*hashMap).size = newSize;
    for (int i = 0; i < oldsize; i++) {
        if (oldarray[i].key == 0) {
            continue;
        } else {
            (*hashMap).array[doubleHash(oldarray[i].key, (hashMap))] = oldarray[i];
        }
    }
    free(oldarray);
}

void add_new_element(HashMap *hashMap, char *key, int value) {
    hashMap->fullness = hashMap->fullness + 1;
    if (hashMap->fullness > max_load * hashMap->size) {
        biggerarray(hashMap,hashMap->size*size_factor);
    }
    HashMapEntry newEntry;
    newEntry.key = key;
    newEntry.value = value;
    hashMap->array[doubleHash(key,hashMap)] = newEntry;
    return;
}

int getValue(HashMap *hashMap, char* str) {
    return (*hashMap).array[doubleHash(str, hashMap)].value;
}