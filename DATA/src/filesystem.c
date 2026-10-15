#include "simulator.h"

FileNode* scan_real_directory(const char *dir_path) {
    FileNode *root = (FileNode*)malloc(sizeof(FileNode));
    strncpy(root->name, dir_path, MAX_NAME - 1);
    root->is_directory = 1;
    root->first_child = NULL;
    root->next_sibling = NULL;
    return root;
}

void free_file_tree(FileNode *root) {
    if (root) free(root);
}