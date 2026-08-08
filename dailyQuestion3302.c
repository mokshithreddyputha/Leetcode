#include <stdlib.h>
#include <string.h>

int* validSequence(char* word1, char* word2, int* returnSize) {

    int n = strlen(word1);
    int m = strlen(word2);

    int* ans = (int*)malloc(m * sizeof(int));

    int* last = (int*)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++)
        last[i] = -1;

    // Build last[]
    int i = n - 1;
    int j = m - 1;

    while (i >= 0 && j >= 0) {

        if (word1[i] == word2[j]) {
            last[j] = i;
            j--;
        }

        i--;
    }

    bool canSkip = true;

    j = 0;

    for (i = 0; i < n; i++) {

        if (j == m)
            break;

        // Exact match
        if (word1[i] == word2[j]) {

            ans[j] = i;
            j++;
        }

        // Use one mismatch
        else if (canSkip &&
                 (j == m - 1 || i < last[j + 1])) {

            canSkip = false;
            ans[j] = i;
            j++;
        }
    }

    free(last);

    if (j != m) {
        free(ans);
        *returnSize = 0;
        return NULL;
    }

    *returnSize = m;
    return ans;
}