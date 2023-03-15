#include "standart.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

#define hashmap_min_size 10
#define max_load 0.5f
#define size_factor 2

struct HashMapEntry {
    String key;
    int value;
};

struct HashMap {
    struct HashMapEntry array[];
    int fullness;
    int size;
};

struct HashMap initilizeHashMap() {
    struct HashMap a;
    a.array = calloc(hashmap_min_size, sizeof(HashMapEntry));
    a.fullness = 0;
    a.size= hashmap_min_size;
    return a;
}

void add_new_element(struct HashMap hashMap,String string, int value) {

}

int hash(String string, ) {
    for (int i=0;i<string.size;i++) {

    }
}