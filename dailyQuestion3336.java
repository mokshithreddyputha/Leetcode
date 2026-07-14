class dailyQuestion3336 {

    public static void main(String[] args) {

        int[] nums = {1, 2, 3};

        Solution obj = new Solution();

        int result = obj.subsequencePairCount(nums);

        System.out.println("Number of valid pairs = " + result);
    }
}

class Solution {

    static final int MOD = 1_000_000_007;

    public int subsequencePairCount(int[] nums) {

        long[][] dp = new long[201][201];
        dp[0][0] = 1; // both subsequences are empty initially

        for (int x : nums) {

            long[][] next = new long[201][201];

            for (int g1 = 0; g1 <= 200; g1++) {
                for (int g2 = 0; g2 <= 200; g2++) {

                    long ways = dp[g1][g2];

                    if (ways == 0) {
                        continue;
                    }

                    // Ignore current element
                    next[g1][g2] =
                            (next[g1][g2] + ways) % MOD;

                    // Put current element into seq1
                    int ng1 = (g1 == 0) ? x : gcd(g1, x);

                    next[ng1][g2] =
                            (next[ng1][g2] + ways) % MOD;

                    // Put current element into seq2
                    int ng2 = (g2 == 0) ? x : gcd(g2, x);

                    next[g1][ng2] =
                            (next[g1][ng2] + ways) % MOD;
                }
            }

            dp = next;
        }

        long ans = 0;

        // Both subsequences must be non-empty and have equal GCD
        for (int g = 1; g <= 200; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int) ans;
    }

    private static int gcd(int a, int b) {

        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }

        return a;
    }
}