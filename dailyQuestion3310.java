class Solution {
    public List<Integer> remainingMethods(int n, int k, int[][] invocations) {

        List<Integer>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++)
            graph[i] = new ArrayList<>();

        for (int[] e : invocations)
            graph[e[0]].add(e[1]);

        boolean[] suspicious = new boolean[n];

        dfs(k, graph, suspicious);

        for (int[] e : invocations) {
            if (!suspicious[e[0]] && suspicious[e[1]]) {
                List<Integer> ans = new ArrayList<>();
                for (int i = 0; i < n; i++)
                    ans.add(i);
                return ans;
            }
        }

        List<Integer> ans = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.add(i);
        }

        return ans;
    }

    private void dfs(int node, List<Integer>[] graph, boolean[] vis) {
        if (vis[node])
            return;

        vis[node] = true;

        for (int next : graph[node])
            dfs(next, graph, vis);
    }
}