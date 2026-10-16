#include "simulator.h"

AttackGraph* create_attack_graph(int vertices) {
    AttackGraph *graph = (AttackGraph*)malloc(sizeof(AttackGraph));
    graph->num_vertices = vertices;
    graph->nodes = (GraphNode*)malloc(vertices * sizeof(GraphNode));
    for (int i = 0; i < vertices; i++) {
        graph->nodes[i].id = i;
        graph->nodes[i].label[0] = '\0';
        graph->nodes[i].head = NULL;
    }
    return graph;
}

void set_node_label(AttackGraph *graph, int node_id, const char *label) {
    if (node_id >= 0 && node_id < graph->num_vertices) {
        strncpy(graph->nodes[node_id].label, label, MAX_NAME - 1);
    }
}

void add_attack_edge(AttackGraph *graph, int src, int dest, int exploit_time) {
    AdjListNode *node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->dest_node_id = dest;
    node->exploit_time_sec = exploit_time;
    node->next = graph->nodes[src].head;
    graph->nodes[src].head = node;
}

void free_attack_graph(AttackGraph *graph) {
    if (!graph) return;
    for (int i = 0; i < graph->num_vertices; i++) {
        AdjListNode *curr = graph->nodes[i].head;
        while (curr) {
            AdjListNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->nodes);
    free(graph);
}