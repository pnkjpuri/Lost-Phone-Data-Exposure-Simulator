// src/main.c - Dual Mode Execution (CLI Scan & Interactive Scenario Engine)
#include "simulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int hide_notifications;
    int enable_fde;
    int enable_app_lock;
} SecurityToggles;

int main(int argc, char *argv[]) {
    const char *target_dir = "mock_phone";
    SecurityToggles toggles = {0, 0, 0};

    // Parse command line arguments for interactive web toggles
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--hide-notifs") == 0) toggles.hide_notifications = 1;
        if (strcmp(argv[i], "--enable-fde") == 0) toggles.enable_fde = 1;
        if (strcmp(argv[i], "--app-lock") == 0) toggles.enable_app_lock = 1;
        if (argv[i][0] != '-') target_dir = argv[i];
    }

    MaxHeap *risk_heap = create_max_heap(50);
    FileNode *root = scan_real_directory(target_dir);

    // 1. Module 1: File Exposure Calculation
    int exposed_files = 0;
    if (!toggles.enable_fde) {
        if (risk_heap) {
            insert_risk_item(risk_heap, "bank_passwords.txt", 98);
            if (!toggles.enable_app_lock) {
                insert_risk_item(risk_heap, "national_id_card.pdf", 95);
                insert_risk_item(risk_heap, "credit_card_screenshot.png", 90);
            }
        }
        exposed_files = toggles.enable_app_lock ? 1 : 3;
    }

    // 2. Module 2 & 3: Attack Path Engine (Dijkstra + Min-Heap)
    AttackGraph *graph = create_attack_graph(5);
    set_node_label(graph, 0, "Physical Access");
    set_node_label(graph, 1, "Lockscreen Notification Preview");
    set_node_label(graph, 2, "2FA OTP Interception");
    set_node_label(graph, 3, "Notes Plaintext Extraction");
    set_node_label(graph, 4, "Bank Account Takeover");

    // Dynamic edge weight calculation based on security mitigations
    int otpt_time = toggles.hide_notifications ? INF : 15;
    int notes_time = toggles.enable_app_lock ? INF : 20;
    int fde_penalty = toggles.enable_fde ? 300 : 0;

    add_attack_edge(graph, 0, 1, 10 + fde_penalty);
    add_attack_edge(graph, 1, 2, otpt_time);
    add_attack_edge(graph, 0, 3, notes_time + fde_penalty);
    add_attack_edge(graph, 2, 4, 25);
    add_attack_edge(graph, 3, 4, 15);

    int path_nodes[10];
    int path_len = 0;
    int attack_time = run_dijkstra_pathfinder(graph, 0, 4, path_nodes, &path_len);

    if (attack_time >= INF / 2) attack_time = 999; // Path blocked by controls

    // Calculate dynamic threat exposure percentage
    int base_risk = 100 - (attack_time / 3);
    if (toggles.enable_fde) base_risk -= 50;
    if (toggles.hide_notifications) base_risk -= 20;
    if (toggles.enable_app_lock) base_risk -= 20;
    if (base_risk < 5) base_risk = 5; // Minimal residual risk

    // 3. Module 4: Hash Table Credentials
    HashTable *vault = create_hash_table();

    // Output JSON for Web Dashboard
    printf("{\n");
    printf("  \"target_dir\": \"%s\",\n", target_dir);
    printf("  \"exposure_score\": %d,\n", base_risk);
    printf("  \"attack_time_seconds\": %d,\n", attack_time);
    printf("  \"exposed_files_count\": %d,\n", exposed_files);
    printf("  \"mitigations\": {\n");
    printf("    \"hide_notifications\": %s,\n", toggles.hide_notifications ? "true" : "false");
    printf("    \"enable_fde\": %s,\n", toggles.enable_fde ? "true" : "false");
    printf("    \"enable_app_lock\": %s\n", toggles.enable_app_lock ? "true" : "false");
    printf("  },\n");
    
    printf("  \"attack_path\": [");
    if (attack_time == 999) {
        printf("\"Attack Path Blocked by Active Mitigations\"");
    } else {
        for (int i = 0; i < path_len; i++) {
            printf("\"%s\"%s", graph->nodes[path_nodes[i]].label, (i < path_len - 1) ? ", " : "");
        }
    }
    printf("],\n");

    printf("  \"ranked_assets\": [\n");
    int count = risk_heap->size;
    for (int i = 0; i < count; i++) {
        RiskItem item = extract_highest_risk(risk_heap);
        printf("    {\"name\": \"%s\", \"score\": %d}%s\n", 
               item.item_name, item.risk_score, (i < count - 1) ? "," : "");
    }
    printf("  ]\n");
    printf("}\n");

    free_file_tree(root);
    free_attack_graph(graph);
    free_hash_table(vault);
    free_max_heap(risk_heap);

    return 0;
}