#include "simulator.h"

MaxHeap* create_max_heap(int capacity) {
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->arr = (RiskItem*)malloc(capacity * sizeof(RiskItem));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insert_risk_item(MaxHeap *heap, const char *name, int score, const char *domain) {
    if (heap->size >= heap->capacity) return;
    strncpy(heap->arr[heap->size].item_name, name, MAX_NAME - 1);
    heap->arr[heap->size].risk_score = score;
    strncpy(heap->arr[heap->size].domain, domain, 31);
    heap->size++;
}

RiskItem extract_highest_risk(MaxHeap *heap) {
    if (heap->size <= 0) {
        RiskItem empty = {"None", 0, "None"};
        return empty;
    }
    int max_idx = 0;
    for (int i = 1; i < heap->size; i++) {
        if (heap->arr[i].risk_score > heap->arr[max_idx].risk_score) max_idx = i;
    }
    RiskItem item = heap->arr[max_idx];
    heap->arr[max_idx] = heap->arr[heap->size - 1];
    heap->size--;
    return item;
}

void free_max_heap(MaxHeap *heap) {
    if (!heap) return;
    free(heap->arr);
    free(heap);
}