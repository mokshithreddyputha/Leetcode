#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1000000007;

class Solution {
public:
    int gcd(int a, int b) {
        while (b) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    int subsequencePairCount(vector<int>& nums) {

        long long dp[201][201] = {};
        dp[0][0] = 1;

        for (int x : nums) {

            long long next[201][201] = {};

            for (int g1 = 0; g1 <= 200; g1++) {
                for (int g2 = 0; g2 <= 200; g2++) {

                    if (dp[g1][g2] == 0)
                        continue;

                    // Ignore current element
                    next[g1][g2] =
                        (next[g1][g2] + dp[g1][g2]) % MOD;

                    // Put current element into seq1
                    int ng1 = (g1 == 0) ? x : gcd(g1, x);
                    next[ng1][g2] =
                        (next[ng1][g2] + dp[g1][g2]) % MOD;

                    // Put current element into seq2
                    int ng2 = (g2 == 0) ? x : gcd(g2, x);
                    next[g1][ng2] =
                        (next[g1][ng2] + dp[g1][g2]) % MOD;
                }
            }

            memcpy(dp, next, sizeof(dp));
        }

        long long ans = 0;

        // Both subsequences must be non-empty and have equal GCD
        for (int g = 1; g <= 200; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};

int main() {

    vector<int> nums = {1, 2, 3};

    Solution obj;

    int result = obj.subsequencePairCount(nums);

    cout << "Number of valid pairs = " << result << endl;

    return 0;
}