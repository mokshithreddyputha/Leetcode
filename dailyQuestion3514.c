#include <stdbool.h>
#include <string.h>

int uniqueXorTriplets(int* nums, int numsSize) {
    const int MAX = 2048;

    bool dp[4][2048] = {false};
    bool next[4][2048];

    dp[0][0] = true;

    for (int i = 0; i < numsSize; i++) {
        int v = nums[i];

        memset(next, 0, sizeof(next));

        // Don't take current element
        for (int c = 0; c <= 3; c++) {
            memcpy(next[c], dp[c], sizeof(dp[c]));
        }

        // Take current element 1, 2, or 3 times
        for (int c = 0; c <= 3; c++) {
            for (int x = 0; x < MAX; x++) {
                if (!dp[c][x]) continue;

                // Take once
                if (c + 1 <= 3)
                    next[c + 1][x ^ v] = true;

                // Take twice (v ^ v = 0)
                if (c + 2 <= 3)
                    next[c + 2][x] = true;

                // Take three times
                if (c + 3 <= 3)
                    next[c + 3][x ^ v] = true;
            }
        }

        memcpy(dp, next, sizeof(dp));
    }

    int ans = 0;
    for (int x = 0; x < MAX; x++) {
        if (dp[3][x])
            ans++;
    }

    return ans;
}