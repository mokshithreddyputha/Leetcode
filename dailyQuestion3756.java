import java.util.*;

class Solution {
    static final int MOD = 1000000007;

    public int[] sumAndMultiply(String s, int[][] queries) {
        int n = s.length();

        // positions and values of non-zero digits
        ArrayList<Integer> pos = new ArrayList<>();
        ArrayList<Integer> val = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int d = s.charAt(i) - '0';
            if (d != 0) {
                pos.add(i);
                val.add(d);
            }
        }

        int m = val.size();

        long[] prefixSum = new long[m + 1];
        long[] prefixNum = new long[m + 1];
        long[] pow10 = new long[m + 1];

        pow10[0] = 1;
        for (int i = 1; i <= m; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        for (int i = 0; i < m; i++) {
            prefixSum[i + 1] = prefixSum[i] + val.get(i);
            prefixNum[i + 1] =
                (prefixNum[i] * 10 + val.get(i)) % MOD;
        }

        int[] answer = new int[queries.length];

        for (int q = 0; q < queries.length; q++) {
            int l = queries[q][0];
            int r = queries[q][1];

            int left = lowerBound(pos, l);
            int right = upperBound(pos, r);

            if (left == right) {
                answer[q] = 0;
                continue;
            }

            long sum = prefixSum[right] - prefixSum[left];

            int len = right - left;

            long x =
                (prefixNum[right]
                - prefixNum[left] * pow10[len] % MOD
                + MOD) % MOD;

            answer[q] = (int)((x * sum) % MOD);
        }

        return answer;
    }

    private int lowerBound(ArrayList<Integer> arr, int target) {
        int l = 0, r = arr.size();

        while (l < r) {
            int mid = (l + r) / 2;

            if (arr.get(mid) < target)
                l = mid + 1;
            else
                r = mid;
        }

        return l;
    }

    private int upperBound(ArrayList<Integer> arr, int target) {
        int l = 0, r = arr.size();

        while (l < r) {
            int mid = (l + r) / 2;

            if (arr.get(mid) <= target)
                l = mid + 1;
            else
                r = mid;
        }

        return l;
    }
}