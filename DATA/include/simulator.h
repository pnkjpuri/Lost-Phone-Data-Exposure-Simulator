#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 256
#define HASH_SIZE 31
#define INF 999999

// ============================================================================
// HASH TABLE: O(1) Security Control Flag Lookup Engine
// ============================================================================
typedef struct ControlFlag {
    char key[MAX_NAME];
    int enabled;
    struct ControlFlag *next;
} ControlFlag;

typedef struct {
    ControlFlag *buckets[HASH_SIZE];
} SecurityControlHashTable;

SecurityControlHashTable* create_control_hash_table();
void set_control_flag(SecurityControlHashTable *ht, const char *key, int value);
int get_control_flag(SecurityControlHashTable *ht, const char *key);
void free_control_hash_table(SecurityControlHashTable *ht);

// ============================================================================
// FILE SYSTEM TREE: N-ary Tree Representation
// ============================================================================
typedef struct FileNode {
    char name[MAX_NAME];
    int is_directory;
    struct FileNode *first_child;
    struct FileNode *next_sibling;
} FileNode;

FileNode* scan_real_directory(const char *dir_path);
void free_file_tree(FileNode *root);

// ============================================================================
// ATTACK GRAPH ENGINE: Directed Graph + Dijkstra Pathfinder
// ============================================================================
typedef struct AdjListNode {
    int dest_node_id;
    int exploit_time_sec;
    struct AdjListNode *next;
} AdjListNode;

typedef struct GraphNode {
    int id;
    char label[MAX_NAME];
    AdjListNode *head;
} GraphNode;

typedef struct AttackGraph {
    int num_vertices;
    GraphNode *nodes;
} AttackGraph;

AttackGraph* create_attack_graph(int vertices);
void set_node_label(AttackGraph *graph, int node_id, const char *label);
void add_attack_edge(AttackGraph *graph, int src, int dest, int exploit_time);
void free_attack_graph(AttackGraph *graph);
int run_dijkstra_pathfinder(AttackGraph *graph, int src, int dest, int *path_nodes, int *path_len);

// ============================================================================
// MAX-HEAP: Priority Asset Risk Evaluator
// ============================================================================
typedef struct RiskItem {
    char item_name[MAX_NAME];
    int risk_score;
    char domain[32]; // Identity, Financial, Work/Cloud
} RiskItem;

typedef struct MaxHeap {
    RiskItem *arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* create_max_heap(int capacity);
void insert_risk_item(MaxHeap *heap, const char *name, int score, const char *domain);
RiskItem extract_highest_risk(MaxHeap *heap);
void free_max_heap(MaxHeap *heap);

#endif