#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "search_algorithms.h"

#define ARRAY_SIZE 20
#define MAX_VALUE 100
#define MAX_BAR_LENGTH 50

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_bar_graph(int arr[], int size, int highlight) {
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }

    for (int i = 0; i < size; i++) {
        int bar_length = (arr[i] * MAX_BAR_LENGTH) / max_val;
        printf("%3d |", arr[i]);
        for (int j = 0; j < bar_length; j++) {
            if (i == highlight) {
                printf("*");
            } else {
                printf("#");
            }
        }
        if (i == highlight) printf(" <-- Current");
        printf("\n");
    }
}

void visualize_search(int arr[], int size, const char* algo_name, int (*search_func)(int[], int, int), int target) {
    printf("\n%s:\n", algo_name);
    int result = search_func(arr, size, target);
    print_bar_graph(arr, size, result);
    printf("Result: %s (index: %d)\n", result != -1 ? "Found" : "Not found", result);
}

void visualize_binary_search(int arr[], int size, int target) {
    printf("\nBinary Search:\n");
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        print_bar_graph(arr, size, mid);
        printf("Left: %d, Right: %d, Mid: %d\n", left, right, mid);
        
        if (arr[mid] == target) {
            printf("Target found at index %d\n", mid);
            return;
        }
        
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
        
        printf("Press Enter to continue...");
        getchar();
    }
    printf("Target not found\n");
}

void visualize_graph(Graph* graph) {
    printf("\nGraph Visualization:\n");
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%d: ", i);
        Node* temp = graph->adj_lists[i];
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("\nGraph Structure:\n");
    printf("0 --- 1 --- 3\n");
    printf("|     |     |\n");
    printf("|     |     |\n");
    printf("2 --- 4 --- 7\n");
    printf("|     |     |\n");
    printf("|     |     |\n");
    printf("5 --- 6 --- 9\n");
    printf(" \\   /\n");
    printf("  \\ /\n");
    printf("   8\n");
}

void print_tree(int* parent, int v, int depth) {
    for (int i = 0; i < depth; i++) {
        printf(i == depth - 1 ? "├── " : "│   ");
    }
    printf("%d\n", v);
    for (int i = 0; i < 10; i++) {
        if (parent[i] == v) {
            print_tree(parent, i, depth + 1);
        }
    }
}

void visualize_dfs(Graph* graph, int start_vertex) {
    printf("\nDepth-First Search starting from vertex %d:\n", start_vertex);
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    int* parent = malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) parent[i] = -1;

    void dfs_util(int v) {
        visited[v] = true;
        printf("%d ", v);

        Node* temp = graph->adj_lists[v];
        while (temp) {
            int adj_v = temp->vertex;
            if (!visited[adj_v]) {
                parent[adj_v] = v;
                dfs_util(adj_v);
            }
            temp = temp->next;
        }
    }

    dfs_util(start_vertex);
    printf("\n\nDFS Tree:\n");
    print_tree(parent, start_vertex, 0);

    free(visited);
    free(parent);
}

void visualize_bfs(Graph* graph, int start_vertex) {
    printf("\nBreadth-First Search starting from vertex %d:\n", start_vertex);
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    int* queue = malloc(graph->num_vertices * sizeof(int));
    int front = 0, rear = 0;
    int* parent = malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) parent[i] = -1;

    visited[start_vertex] = true;
    queue[rear++] = start_vertex;

    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);

        Node* temp = graph->adj_lists[v];
        while (temp) {
            int adj_v = temp->vertex;
            if (!visited[adj_v]) {
                visited[adj_v] = true;
                queue[rear++] = adj_v;
                parent[adj_v] = v;
            }
            temp = temp->next;
        }
    }

    printf("\n\nBFS Tree:\n");
    print_tree(parent, start_vertex, 0);

    free(visited);
    free(queue);
    free(parent);
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[ARRAY_SIZE];
    int target;

    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % MAX_VALUE;
    }
    qsort(arr, ARRAY_SIZE, sizeof(int), compare);

    printf("Sorted array: ");
    print_array(arr, ARRAY_SIZE);

    target = arr[rand() % ARRAY_SIZE];
    printf("Target: %d\n", target);

    visualize_search(arr, ARRAY_SIZE, "Linear Search", linear_search, target);
    visualize_binary_search(arr, ARRAY_SIZE, target);
    visualize_search(arr, ARRAY_SIZE, "Jump Search", jump_search, target);
    visualize_search(arr, ARRAY_SIZE, "Interpolation Search", (int (*)(int[], int, int))interpolation_search, target);

    Graph* graph = create_graph(10);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 5);
    add_edge(graph, 2, 6);
    add_edge(graph, 3, 7);
    add_edge(graph, 4, 7);
    add_edge(graph, 5, 8);
    add_edge(graph, 6, 8);
    add_edge(graph, 7, 9);
    add_edge(graph, 8, 9);

    visualize_graph(graph);
    visualize_dfs(graph, 0);
    visualize_bfs(graph, 0);

    free_graph(graph);

    return 0;
}
