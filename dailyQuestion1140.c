#include <stdlib.h>

int stoneGameII(int* piles, int pilesSize) {

    int n = pilesSize;

    // suffix[i] = sum of piles from i to n-1
    int* suffix = (int*)calloc(n + 1, sizeof(int));

    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = suffix[i + 1] + piles[i];
    }

    // dp[i][M]
    int** dp = (int**)malloc((n + 1) * sizeof(int*));

    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(n + 1, sizeof(int));
    }

    for (int i = n - 1; i >= 0; i--) {

        for (int M = 1; M <= n; M++) {

            // Take all remaining piles
            if (i + 2 * M >= n) {
                dp[i][M] = suffix[i];
                continue;
            }

            int best = 0;

            for (int X = 1; X <= 2 * M; X++) {

                int nextM = (M > X) ? M : X;

                int current =
                    suffix[i] - dp[i + X][nextM];

                if (current > best)
                    best = current;
            }

            dp[i][M] = best;
        }
    }

    int answer = dp[0][1];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }

    free(dp);
    free(suffix);

    return answer;
}