#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Note: The returned string must be malloced, assume caller calls free().
 */
char* smallestSubsequence(char* s) {
    int n = strlen(s);

    int last[26];
    bool used[26] = {false};

    // Store the last occurrence of each character
    for (int i = 0; i < n; i++) {
        last[s[i] - 'a'] = i;
    }

    char *stack = (char *)malloc(27 * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];

        if (used[c - 'a'])
            continue;

        while (top >= 0 &&
               stack[top] > c &&
               last[stack[top] - 'a'] > i) {
            used[stack[top] - 'a'] = false;
            top--;
        }

        stack[++top] = c;
        used[c - 'a'] = true;
    }

    stack[top + 1] = '\0';
    return stack;
}

int main() {

    char s[] = "cbacdcbc";

    char *result = smallestSubsequence(s);

    printf("Smallest Subsequence: %s\n", result);

    free(result);

    return 0;
}