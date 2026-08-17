int stoneGameV(int* stoneValue, int stoneValueSize) {
    int n = stoneValueSize;

    int prefix[n + 1];
    int dp[n][n];

    for (int i = 0; i <= n; i++)
        prefix[i] = 0;

    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + stoneValue[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = 0;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {

            int r = l + len - 1;

            for (int k = l; k < r; k++) {

                int left = prefix[k + 1] - prefix[l];
                int right = prefix[r + 1] - prefix[k + 1];

                int value;

                if (left < right) {
                    value = left + dp[l][k];
                }
                else if (left > right) {
                    value = right + dp[k + 1][r];
                }
                else {
                    int a = dp[l][k];
                    int b = dp[k + 1][r];

                    value = left + (a > b ? a : b);
                }

                if (value > dp[l][r])
                    dp[l][r] = value;
            }
        }
    }

    return dp[0][n - 1];
}