#include "standart.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

#define hashmap_min_size 10
#define max_load 0.5f
#define size_factor 2



HashMap initializeHashMap() {
    HashMap a;
    a.array = (HashMapEntry*) calloc(hashmap_min_size, sizeof(HashMapEntry));
    a.fullness = 0;
    a.size= hashmap_min_size;
    return a;
}

void add_new_element(HashMap* hashMap,char* str, int value) {
    return;
}

int hash(char *str, int size) {
    int hash = 0;
    int i = 0;
    while (str[i] != 0) {
        hash = ((hash << 3) + str[i] - 'a' + 1) % size;
    }
    return hash;
}

int doubleHash(char *str, HashMap hashMap) {
    int i = 0;
    int firstHash = hash(str, hashMap.size);
    while (1) {
        if (hashMap.array[(firstHash+i)*(i+1)].key == 0) {
            return (firstHash+i)*(i+1);
        } else {
            i++;
        }
    }
}

void biggerarray(struct HashMap hashMap, int newSize) {
    hashMap.array = (struct HashMapEntry*) calloc(newSize, sizeof(struct HashMapEntry));

}