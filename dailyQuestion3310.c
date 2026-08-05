#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

void dfs(int u, Node** graph, bool* vis) {
    if (vis[u]) return;
    vis[u] = true;

    Node* cur = graph[u];
    while (cur) {
        dfs(cur->val, graph, vis);
        cur = cur->next;
    }
}

int* remainingMethods(int n, int k, int** invocations, int invocationsSize,
                      int* invocationsColSize, int* returnSize) {

    Node** graph = (Node**)calloc(n, sizeof(Node*));

    for (int i = 0; i < invocationsSize; i++) {
        int u = invocations[i][0];
        int v = invocations[i][1];

        Node* node = (Node*)malloc(sizeof(Node));
        node->val = v;
        node->next = graph[u];
        graph[u] = node;
    }

    bool* suspicious = (bool*)calloc(n, sizeof(bool));

    dfs(k, graph, suspicious);

    for (int i = 0; i < invocationsSize; i++) {
        int u = invocations[i][0];
        int v = invocations[i][1];

        if (!suspicious[u] && suspicious[v]) {
            int* ans = (int*)malloc(n * sizeof(int));
            for (int j = 0; j < n; j++)
                ans[j] = j;
            *returnSize = n;
            return ans;
        }
    }

    int* ans = (int*)malloc(n * sizeof(int));
    int idx = 0;

    for (int i = 0; i < n; i++)
        if (!suspicious[i])
            ans[idx++] = i;

    *returnSize = idx;
    return ans;
}