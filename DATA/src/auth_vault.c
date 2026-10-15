#include "simulator.h"

HashTable* create_hash_table() {
    return (HashTable*)malloc(sizeof(HashTable));
}

void free_hash_table(HashTable *ht) {
    if (ht) free(ht);
}