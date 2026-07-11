import java.util.*;

class _2685 {

    public static void main(String[] args) {

        int n = 6;

        int[][] edges = {
            {0, 1},
            {0, 2},
            {1, 2},
            {3, 4}
        };

        Solution obj = new Solution();

        int result = obj.countCompleteComponents(n, edges);

        System.out.println("Complete Components = " + result);
    }
}

class Solution {

    private void dfs(int node, List<Integer>[] adj, boolean[] visited,
                     int[] vertices, int[] degreeSum) {

        visited[node] = true;
        vertices[0]++;
        degreeSum[0] += adj[node].size();

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, vertices, degreeSum);
            }
        }
    }

    public int countCompleteComponents(int n, int[][] edges) {

        List<Integer>[] adj = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }

        for (int[] edge : edges) {
            adj[edge[0]].add(edge[1]);
            adj[edge[1]].add(edge[0]);
        }

        boolean[] visited = new boolean[n];
        int completeComponents = 0;

        for (int i = 0; i < n; i++) {

            if (!visited[i]) {

                int[] vertices = new int[1];
                int[] degreeSum = new int[1];

                dfs(i, adj, visited, vertices, degreeSum);

                int edgeCount = degreeSum[0] / 2;
                int requiredEdges = vertices[0] * (vertices[0] - 1) / 2;

                if (edgeCount == requiredEdges) {
                    completeComponents++;
                }
            }
        }

        return completeComponents;
    }
}