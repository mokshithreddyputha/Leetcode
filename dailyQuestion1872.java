class Solution {
    public int stoneGameVIII(int[] stones) {

        int n = stones.length;

        long[] prefix = new long[n];

        prefix[0] = stones[0];

        // Build prefix sum
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + stones[i];
        }

        // Taking all stones is one possible move
        long dp = prefix[n - 1];

        // Consider taking first 2, 3, ..., n-1 stones
        for (int i = n - 2; i >= 1; i--) {

            dp = Math.max(dp, prefix[i] - dp);
        }

        return (int) dp;
    }
}