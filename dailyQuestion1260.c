#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *returnColumnSizes must be malloced.
 */
int** shiftGrid(int** grid, int gridSize, int* gridColSize, int k,
                int* returnSize, int** returnColumnSizes) {

    int m = gridSize;
    int n = gridColSize[0];
    int total = m * n;

    k %= total;

    int **ans = (int **)malloc(m * sizeof(int *));
    *returnColumnSizes = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        ans[i] = (int *)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            int index = i * n + j;
            int newIndex = (index + k) % total;

            int newRow = newIndex / n;
            int newCol = newIndex % n;

            ans[newRow][newCol] = grid[i][j];
        }
    }

    *returnSize = m;
    return ans;
}

int main() {

    int m = 3, n = 3;

    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9};

    int *grid[] = {row0, row1, row2};

    int gridColSize[] = {3, 3, 3};

    int k = 1;

    int returnSize;
    int *returnColumnSizes;

    int **result = shiftGrid(
        grid,
        m,
        gridColSize,
        k,
        &returnSize,
        &returnColumnSizes
    );

    printf("Shifted Grid:\n");

    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }

    free(result);
    free(returnColumnSizes);

    return 0;
}