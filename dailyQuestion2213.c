#include <stdlib.h>

typedef struct {
    char leftChar;
    char rightChar;
    
    int prefix;
    int suffix;
    int best;
    int length;
} Node;

Node* tree;
char* str;

Node makeNode(char c) {
    
    Node node;
    
    node.leftChar = c;
    node.rightChar = c;
    
    node.prefix = 1;
    node.suffix = 1;
    node.best = 1;
    node.length = 1;
    
    return node;
}

Node merge(Node a, Node b) {
    
    Node result;
    
    result.length = a.length + b.length;
    
    result.leftChar = a.leftChar;
    result.rightChar = b.rightChar;
    
    result.prefix = a.prefix;
    result.suffix = b.suffix;
    
    result.best = a.best > b.best
                    ? a.best
                    : b.best;
    
    // Boundary characters are equal
    if (a.rightChar == b.leftChar) {
        
        // Entire left segment has same character
        if (a.prefix == a.length) {
            result.prefix =
                a.length + b.prefix;
        }
        
        // Entire right segment has same character
        if (b.suffix == b.length) {
            result.suffix =
                b.length + a.suffix;
        }
        
        // Join suffix of left and prefix of right
        int combined =
            a.suffix + b.prefix;
        
        if (combined > result.best) {
            result.best = combined;
        }
    }
    
    return result;
}

void build(int node, int left, int right) {
    
    if (left == right) {
        tree[node] = makeNode(str[left]);
        return;
    }
    
    int mid = (left + right) / 2;
    
    build(
        node * 2,
        left,
        mid
    );
    
    build(
        node * 2 + 1,
        mid + 1,
        right
    );
    
    tree[node] = merge(
        tree[node * 2],
        tree[node * 2 + 1]
    );
}

void update(
    int node,
    int left,
    int right,
    int index,
    char c
) {
    
    if (left == right) {
        tree[node] = makeNode(c);
        return;
    }
    
    int mid = (left + right) / 2;
    
    if (index <= mid) {
        
        update(
            node * 2,
            left,
            mid,
            index,
            c
        );
        
    } else {
        
        update(
            node * 2 + 1,
            mid + 1,
            right,
            index,
            c
        );
    }
    
    tree[node] = merge(
        tree[node * 2],
        tree[node * 2 + 1]
    );
}

int* longestRepeating(
    char* s,
    char* queryCharacters,
    int* queryIndices,
    int queryIndicesSize,
    int* returnSize
) {
    
    int n = 0;
    
    // Find string length
    while (s[n] != '\0') {
        n++;
    }
    
    str = s;
    
    // Segment tree
    tree = (Node*)malloc(
        sizeof(Node) * 4 * n
    );
    
    // Build tree
    build(
        1,
        0,
        n - 1
    );
    
    int* ans = (int*)malloc(
        sizeof(int) * queryIndicesSize
    );
    
    for (int i = 0; i < queryIndicesSize; i++) {
        
        int index = queryIndices[i];
        char c = queryCharacters[i];
        
        // Update original string
        str[index] = c;
        
        // Update segment tree
        update(
            1,
            0,
            n - 1,
            index,
            c
        );
        
        // Root contains longest repeating substring
        ans[i] = tree[1].best;
    }
    
    *returnSize = queryIndicesSize;
    
    free(tree);
    
    return ans;
}