#include <stdlib.h>

long long stoneGameVIII(int* stones, int stonesSize) {

    int n = stonesSize;

    long long* prefix =
        (long long*)malloc(n * sizeof(long long));

    prefix[0] = stones[0];

    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + stones[i];
    }

    long long dp = prefix[n - 1];

    for (int i = n - 2; i >= 1; i--) {

        long long option = prefix[i] - dp;

        if (option > dp) {
            dp = option;
        }
    }

    long long answer = dp;

    free(prefix);

    return answer;
}