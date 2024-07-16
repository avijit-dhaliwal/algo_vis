#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <stdbool.h>

int linear_search(int arr[], int n, int x);
int binary_search(int arr[], int l, int r, int x);
int jump_search(int arr[], int n, int x);
int interpolation_search(int arr[], int low, int high, int x);

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    int num_vertices;
    Node** adj_lists;
    bool* visited;
} Graph;

Graph* create_graph(int num_vertices);
void add_edge(Graph* graph, int src, int dest);
void free_graph(Graph* graph);
void dfs(Graph* graph, int vertex);
void bfs(Graph* graph, int start_vertex);

#endif