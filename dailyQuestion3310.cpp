class Solution {
public:
    void dfs(int u, vector<vector<int>>& graph, vector<bool>& vis) {
        if (vis[u]) return;

        vis[u] = true;

        for (int v : graph[u])
            dfs(v, graph, vis);
    }

    vector<int> remainingMethods(int n, int k,
                                 vector<vector<int>>& invocations) {

        vector<vector<int>> graph(n);

        for (auto& e : invocations)
            graph[e[0]].push_back(e[1]);

        vector<bool> suspicious(n, false);

        dfs(k, graph, suspicious);

        for (auto& e : invocations) {
            if (!suspicious[e[0]] && suspicious[e[1]]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        vector<int> ans;

        for (int i = 0; i < n; i++)
            if (!suspicious[i])
                ans.push_back(i);

        return ans;
    }
};