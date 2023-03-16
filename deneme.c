#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main() {
    struct HashMap a;
    a = initializeHashMap();
    add_new_element(a,"bruh", 5);
    add_new_element(a,"ada", 5);
    printf("frisk");
}
