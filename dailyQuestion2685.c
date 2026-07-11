#include <stdlib.h>

void dfs(int node, int** adj, int* adjSize, int* visited,
         int* vertices, int* degreeSum) {
    
    visited[node] = 1;
    (*vertices)++;
    (*degreeSum) += adjSize[node];

    for (int i = 0; i < adjSize[node]; i++) {
        int neighbor = adj[node][i];

        if (!visited[neighbor]) {
            dfs(neighbor, adj, adjSize, visited, vertices, degreeSum);
        }
    }
}

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {

    int* degree = calloc(n, sizeof(int));

    // Count degrees to allocate adjacency list
    for (int i = 0; i < edgesSize; i++) {
        degree[edges[i][0]]++;
        degree[edges[i][1]]++;
    }

    int** adj = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adj[i] = malloc(degree[i] * sizeof(int));
    }

    int* index = calloc(n, sizeof(int));

    // Build adjacency list
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u][index[u]++] = v;
        adj[v][index[v]++] = u;
    }

    int* visited = calloc(n, sizeof(int));
    int completeComponents = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {

            int vertices = 0;
            int degreeSum = 0;

            dfs(i, adj, degree, visited, &vertices, &degreeSum);

            int edgeCount = degreeSum / 2;
            int requiredEdges = vertices * (vertices - 1) / 2;

            if (edgeCount == requiredEdges) {
                completeComponents++;
            }
        }
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(degree);
    free(index);
    free(visited);

    return completeComponents;
}