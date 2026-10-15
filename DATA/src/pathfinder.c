#include "simulator.h"

int run_dijkstra_pathfinder(AttackGraph *graph, int src, int dest, int *path_nodes, int *path_len) {
    int V = graph->num_vertices;
    int dist[32];
    int parent[32];
    int visited[32] = {0};

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min_dist = INF, u = -1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        AdjListNode *curr = graph->nodes[u].head;
        while (curr != NULL) {
            int v = curr->dest_node_id;
            if (!visited[v] && dist[u] != INF && dist[u] + curr->exploit_time_sec < dist[v]) {
                dist[v] = dist[u] + curr->exploit_time_sec;
                parent[v] = u;
            }
            curr = curr->next;
        }
    }

    int curr = dest;
    int count = 0;
    int temp_path[32];

    while (curr != -1) {
        temp_path[count++] = curr;
        curr = parent[curr];
    }

    *path_len = count;
    for (int i = 0; i < count; i++) {
        path_nodes[i] = temp_path[count - 1 - i];
    }

    return dist[dest];
}