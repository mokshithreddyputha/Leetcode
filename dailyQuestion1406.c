#include <stdlib.h>
#include <limits.h>

char* stoneGameIII(int* stoneValue, int stoneValueSize) {
    int n = stoneValueSize;
    int* dp = (int*)calloc(n + 1, sizeof(int));

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = INT_MIN;
        int sum = 0;

        for (int k = 0; k < 3 && i + k < n; k++) {
            sum += stoneValue[i + k];

            int val = sum - dp[i + k + 1];
            if (val > dp[i])
                dp[i] = val;
        }
    }

    char* ans;
    if (dp[0] > 0)
        ans = "Alice";
    else if (dp[0] < 0)
        ans = "Bob";
    else
        ans = "Tie";

    free(dp);
    return ans;
}