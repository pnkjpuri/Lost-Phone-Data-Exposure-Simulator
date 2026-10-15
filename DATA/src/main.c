// src/main.c
#include "simulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    SecurityControlHashTable *controls = create_control_hash_table();
    int time_tick_min = 0;
    int threat_profile = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--hide-notifs") == 0) set_control_flag(controls, "hide_notifs", 1);
        if (strcmp(argv[i], "--app-lock") == 0) set_control_flag(controls, "app_lock", 1);
        if (strcmp(argv[i], "--enable-fde") == 0) set_control_flag(controls, "enable_fde", 1);
        if (strcmp(argv[i], "--sim-pin") == 0) set_control_flag(controls, "sim_pin", 1);
        if (strcmp(argv[i], "--remote-wipe") == 0) set_control_flag(controls, "remote_wipe", 1);
        if (strncmp(argv[i], "--time=", 7) == 0) time_tick_min = atoi(argv[i] + 7);
        if (strcmp(argv[i], "--thief") == 0) threat_profile = 1;
    }

    int f_notifs = get_control_flag(controls, "hide_notifs");
    int f_applock = get_control_flag(controls, "app_lock");
    int f_fde = get_control_flag(controls, "enable_fde");
    int f_simpin = get_control_flag(controls, "sim_pin");
    int f_wipe = get_control_flag(controls, "remote_wipe");

    MaxHeap *risk_heap = create_max_heap(50);
    AttackGraph *graph = create_attack_graph(5);

    set_node_label(graph, 0, "Physical Lockscreen Access");
    set_node_label(graph, 1, "Lock Screen Notification Intercept");
    set_node_label(graph, 2, "Primary Email & 2FA Reset");
    set_node_label(graph, 3, "Notes Plaintext Credentials");
    set_node_label(graph, 4, "Complete Financial & Cloud Takeover");

    int notif_weight = f_notifs ? INF : 10;
    int notes_weight = f_applock ? INF : 15;
    int sim_weight = f_simpin ? INF : 20;

    if (f_wipe && time_tick_min >= 15) {
        notif_weight = INF;
        notes_weight = INF;
        sim_weight = INF;
    }

    add_attack_edge(graph, 0, 1, notif_weight);
    add_attack_edge(graph, 1, 2, sim_weight);
    add_attack_edge(graph, 0, 3, notes_weight);
    add_attack_edge(graph, 2, 4, 15);
    add_attack_edge(graph, 3, 4, 10);

    int path_nodes[10];
    int path_len = 0;
    int attack_time = run_dijkstra_pathfinder(graph, 0, 4, path_nodes, &path_len);

    int display_attack_time = (attack_time >= INF / 2) ? 999 : attack_time;

    int identity_exp = 85, financial_exp = 95, cloud_exp = 70;
    if (f_notifs) { identity_exp -= 25; financial_exp -= 30; }
    if (f_applock) { financial_exp -= 30; cloud_exp -= 35; }
    if (f_simpin) { identity_exp -= 20; financial_exp -= 25; }
    if (f_fde) { identity_exp -= 20; cloud_exp -= 20; }
    if (f_wipe && time_tick_min >= 15) { identity_exp = 5; financial_exp = 5; cloud_exp = 5; }

    if (identity_exp < 5) identity_exp = 5;
    if (financial_exp < 5) financial_exp = 5;
    if (cloud_exp < 5) cloud_exp = 5;

    int overall_risk = (identity_exp + financial_exp + cloud_exp) / 3;

    if (financial_exp > 20) insert_risk_item(risk_heap, "Bank OTP & UPI Apps", financial_exp, "Financial");
    if (identity_exp > 20) insert_risk_item(risk_heap, "Identity Documents (ID/Passport)", identity_exp, "Identity");
    if (cloud_exp > 20) insert_risk_item(risk_heap, "Email & Cloud Storage Sessions", cloud_exp, "Work/Cloud");

    printf("{\n");
    printf("  \"exposure_score\": %d,\n", overall_risk);
    printf("  \"attack_time_seconds\": %d,\n", display_attack_time);
    printf("  \"timeline_min\": %d,\n", time_tick_min);
    printf("  \"domains\": {\n");
    printf("    \"identity\": %d,\n", identity_exp);
    printf("    \"financial\": %d,\n", financial_exp);
    printf("    \"cloud\": %d\n", cloud_exp);
    printf("  },\n");
    printf("  \"attack_path\": [");
    if (display_attack_time == 999) {
        printf("\"Attack Path Blocked by Active Controls (SIM/App Lock/FDE)\"");
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
        printf("    {\"name\": \"%s\", \"score\": %d, \"domain\": \"%s\"}%s\n", 
               item.item_name, item.risk_score, item.domain, (i < count - 1) ? "," : "");
    }
    printf("  ]\n");
    printf("}\n");

    free_control_hash_table(controls);
    free_attack_graph(graph);
    free_max_heap(risk_heap);

    return 0;
}