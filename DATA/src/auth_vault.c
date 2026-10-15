#include "simulator.h"

static unsigned int hash_key(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

SecurityControlHashTable* create_control_hash_table() {
    SecurityControlHashTable *ht = (SecurityControlHashTable*)malloc(sizeof(SecurityControlHashTable));
    for (int i = 0; i < HASH_SIZE; i++) ht->buckets[i] = NULL;
    return ht;
}

void set_control_flag(SecurityControlHashTable *ht, const char *key, int value) {
    unsigned int idx = hash_key(key);
    ControlFlag *curr = ht->buckets[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            curr->enabled = value;
            return;
        }
        curr = curr->next;
    }
    ControlFlag *node = (ControlFlag*)malloc(sizeof(ControlFlag));
    strncpy(node->key, key, MAX_NAME - 1);
    node->enabled = value;
    node->next = ht->buckets[idx];
    ht->buckets[idx] = node;
}

int get_control_flag(SecurityControlHashTable *ht, const char *key) {
    unsigned int idx = hash_key(key);
    ControlFlag *curr = ht->buckets[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr->enabled;
        curr = curr->next;
    }
    return 0; // Default off
}

void free_control_hash_table(SecurityControlHashTable *ht) {
    if (!ht) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        ControlFlag *curr = ht->buckets[i];
        while (curr) {
            ControlFlag *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(ht);
}