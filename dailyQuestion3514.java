class Solution {
    public int uniqueXorTriplets(int[] nums) {
        final int MAX = 2048;

        boolean[][] dp = new boolean[4][MAX];
        dp[0][0] = true;

        for (int v : nums) {
            boolean[][] next = new boolean[4][MAX];

            // Option: don't use current index
            for (int c = 0; c <= 3; c++) {
                System.arraycopy(dp[c], 0, next[c], 0, MAX);
            }

            // Use current index 1, 2, or 3 times
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

            dp = next;
        }

        int ans = 0;
        for (boolean possible : dp[3]) {
            if (possible) ans++;
        }

        return ans;
    }
}