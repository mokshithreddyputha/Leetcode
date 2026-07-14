#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int gcd(int a, int b) {
    while (b) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int subsequencePairCount(int* nums, int numsSize) {

    long long dp[201][201] = {0};
    dp[0][0] = 1;

    for (int idx = 0; idx < numsSize; idx++) {

        int x = nums[idx];
        long long next[201][201] = {0};

        for (int g1 = 0; g1 <= 200; g1++) {
            for (int g2 = 0; g2 <= 200; g2++) {

                if (dp[g1][g2] == 0)
                    continue;

                // Ignore current element
                next[g1][g2] =
                    (next[g1][g2] + dp[g1][g2]) % MOD;

                // Put current element in seq1
                int ng1 = (g1 == 0) ? x : gcd(g1, x);

                next[ng1][g2] =
                    (next[ng1][g2] + dp[g1][g2]) % MOD;

                // Put current element in seq2
                int ng2 = (g2 == 0) ? x : gcd(g2, x);

                next[g1][ng2] =
                    (next[g1][ng2] + dp[g1][g2]) % MOD;
            }
        }

        memcpy(dp, next, sizeof(dp));
    }

    long long ans = 0;

    for (int g = 1; g <= 200; g++) {
        ans = (ans + dp[g][g]) % MOD;
    }

    return (int)ans;
}

int main() {

    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = subsequencePairCount(nums, numsSize);

    printf("Number of valid pairs = %d\n", result);

    return 0;
}