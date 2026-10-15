#include "simulator.h"

MaxHeap* create_max_heap(int capacity) {
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->arr = (RiskItem*)malloc(capacity * sizeof(RiskItem));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insert_risk_item(MaxHeap *heap, const char *name, int score) {
    if (heap->size >= heap->capacity) return;
    strncpy(heap->arr[heap->size].item_name, name, MAX_NAME - 1);
    heap->arr[heap->size].risk_score = score;
    heap->size++;
}

RiskItem extract_highest_risk(MaxHeap *heap) {
    if (heap->size <= 0) {
        RiskItem empty = {"None", 0};
        return empty;
    }
    return heap->arr[--heap->size];
}

void free_max_heap(MaxHeap *heap) {
    if (!heap) return;
    free(heap->arr);
    free(heap);
}