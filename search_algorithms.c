#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "search_algorithms.h"

// Helper function for min value
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Linear Search
int linear_search(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) return i;
    }
    return -1;
}

// Binary Search
int binary_search(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] > x) return binary_search(arr, l, mid - 1, x);
        return binary_search(arr, mid + 1, r, x);
    }
    return -1;
}

// Jump Search
int jump_search(int arr[], int n, int x) {
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n)-1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }
    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) return -1;
    }
    if (arr[prev] == x) return prev;
    return -1;
}

// Interpolation Search
int interpolation_search(int arr[], int low, int high, int x) {
    int pos;
    if (low <= high && x >= arr[low] && x <= arr[high]) {
        pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));
        if (arr[pos] == x) return pos;
        if (arr[pos] < x) return interpolation_search(arr, pos + 1, high, x);
        if (arr[pos] > x) return interpolation_search(arr, low, pos - 1, x);
    }
    return -1;
}

// Graph functions
Graph* create_graph(int num_vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_lists = malloc(num_vertices * sizeof(Node*));
    graph->visited = malloc(num_vertices * sizeof(bool));

    for (int i = 0; i < num_vertices; i++) {
        graph->adj_lists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    Node* new_node = malloc(sizeof(Node));
    new_node->vertex = dest;
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;

    new_node = malloc(sizeof(Node));
    new_node->vertex = src;
    new_node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node;
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        Node* temp = graph->adj_lists[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adj_lists);
    free(graph->visited);
    free(graph);
}

// Depth-First Search
void dfs_util(Graph* graph, int v, bool* visited, int* parent) {
    visited[v] = true;
    printf("%d ", v);

    Node* temp = graph->adj_lists[v];
    while (temp) {
        int adj_v = temp->vertex;
        if (!visited[adj_v]) {
            parent[adj_v] = v;
            dfs_util(graph, adj_v, visited, parent);
        }
        temp = temp->next;
    }
}

void dfs(Graph* graph, int start_vertex) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    int* parent = malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) {
        parent[i] = -1;
    }

    dfs_util(graph, start_vertex, visited, parent);

    free(visited);
    free(parent);
}

// Breadth-First Search
void bfs(Graph* graph, int start_vertex) {
    bool* visited = malloc(graph->num_vertices * sizeof(bool));
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = false;
    }

    int* queue = malloc(graph->num_vertices * sizeof(int));
    int front = 0, rear = 0;

    visited[start_vertex] = true;
    queue[rear++] = start_vertex;

    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        Node* temp = graph->adj_lists[vertex];
        while (temp) {
            int adj_vertex = temp->vertex;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = true;
                queue[rear++] = adj_vertex;
            }
            temp = temp->next;
        }
    }

    printf("\n");
    free(visited);
    free(queue);
}
