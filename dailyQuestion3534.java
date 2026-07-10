import java.util.*;

class dailyQuestion3534 {

    public static void main(String[] args) {

        int n = 5;
        int[] nums = {1, 3, 5, 7, 9};
        int maxDiff = 2;

        int[][] queries = {
            {0, 2},
            {0, 4},
            {1, 3},
            {2, 2}
        };

        Solution obj = new Solution();

        int[] result = obj.pathExistenceQueries(
                n,
                nums,
                maxDiff,
                queries
        );

        System.out.println(Arrays.toString(result));
    }
}

class Solution {

    public int[] pathExistenceQueries(
            int n,
            int[] nums,
            int maxDiff,
            int[][] queries
    ) {

        int[][] arr = new int[n][2];

        for (int i = 0; i < n; i++) {
            arr[i][0] = nums[i];
            arr[i][1] = i;
        }

        Arrays.sort(arr, (a, b) -> Integer.compare(a[0], b[0]));

        // original index -> sorted position
        int[] pos = new int[n];
        for (int i = 0; i < n; i++) {
            pos[arr[i][1]] = i;
        }

        // next[i] = furthest position reachable in one edge
        int[] next = new int[n];
        int r = 0;

        for (int l = 0; l < n; l++) {
            while (r + 1 < n &&
                   arr[r + 1][0] - arr[l][0] <= maxDiff) {
                r++;
            }
            next[l] = r;
        }

        // connected components in sorted order
        int[] comp = new int[n];
        int component = 0;
        comp[0] = component;

        for (int i = 1; i < n; i++) {
            if (arr[i][0] - arr[i - 1][0] > maxDiff) {
                component++;
            }
            comp[i] = component;
        }

        // binary lifting table
        int LOG = 20;
        int[][] up = new int[LOG][n];

        for (int i = 0; i < n; i++) {
            up[0][i] = next[i];
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        int[] answer = new int[queries.length];

        for (int qi = 0; qi < queries.length; qi++) {

            int u = pos[queries[qi][0]];
            int v = pos[queries[qi][1]];

            if (u == v) {
                answer[qi] = 0;
                continue;
            }

            if (u > v) {
                int temp = u;
                u = v;
                v = temp;
            }

            // different connected components
            if (comp[u] != comp[v]) {
                answer[qi] = -1;
                continue;
            }

            int steps = 0;
            int cur = u;

            // jump while staying before v
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < v) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            answer[qi] = steps + 1;
        }

        return answer;
    }
}