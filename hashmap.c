#include "standart.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initializing the minimum size, maximum load and size factor of our Hashmap
#define hashmap_min_size 257
#define max_load 0.5f
#define size_factor 2

// Our Hashmap functions
int doubleHash(char *, HashMap *);
void biggerarray(HashMap *hashMap, int newSize);

// Our Hashmap constructor
HashMap initializeHashMap() {
    HashMap a;
    a.array = (HashMapEntry *) calloc(hashmap_min_size, sizeof(HashMapEntry));
    a.fullness = 0;
    a.size = hashmap_min_size;
    return a;
}

// Our hashing function
int hash(char *str, int size) {
    int hash = 0;
    int i = 0;
    while (str[i] != 0) {
        hash = ((hash << 8) + str[i] - 'a' + 1) % size;
        i++;
    }
    return hash;
}

// In case of a collision in the upper "hash" function, this will be used for hashing
int doubleHash(char *str, HashMap *hashMap) {
    int i = 0;
    int firstHash = hash(str, (*hashMap).size);
    char* key;
    while (TRUE) {
        key = (*hashMap).array[((firstHash + i) * (i + 1)) % (*hashMap).size].key;
        if (key == 0 || (chadstrcmp(key, str)) == 0) {
            return ((firstHash + i) * (i + 1)) % (*hashMap).size;
        } else {
            i++;
        }
    }
}

// Resizing our Hashmap
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

// Adding a new element to our Hashmap
void add_new_element(HashMap *hashMap, char *key, long long int value) {
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

// Getting the value of an element inside our Hashmap
long long int getValue(HashMap *hashMap, char* str) {
    return (*hashMap).array[doubleHash(str, hashMap)].value;
}

// Function which frees the pre-allocated memories inside the Hashmap
void deconstractor(HashMap *hashMap) {
    for(int i = 0; i<(*hashMap).size; i++) {
        if ((*hashMap).array[i].key != 0) {
            free((*hashMap).array[i].key);
        }
    }
    free((*hashMap).array);
}

// String comparator function
int chadstrcmp(char *str1, char*str2) {
    int i = 0;
    while(str1[i] !='\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            return 1;
        }
        i++;
    }
    if (str1[i] =='\0' && str2[i] == '\0') {
        return 0;
    }
    return 1;
}