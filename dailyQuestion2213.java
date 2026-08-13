class Solution {

    class Node {
        char leftChar;
        char rightChar;

        int prefix;
        int suffix;
        int best;
        int length;

        Node() {
        }

        Node(char c) {
            leftChar = c;
            rightChar = c;
            prefix = 1;
            suffix = 1;
            best = 1;
            length = 1;
        }
    }

    Node[] tree;
    char[] s;

    public int[] longestRepeating(
            String s,
            String queryCharacters,
            int[] queryIndices) {

        this.s = s.toCharArray();

        int n = s.length();

        tree = new Node[4 * n];

        for (int i = 0; i < tree.length; i++) {
            tree[i] = new Node();
        }

        build(1, 0, n - 1);

        int[] ans = new int[queryIndices.length];

        for (int q = 0; q < queryIndices.length; q++) {

            int index = queryIndices[q];
            char c = queryCharacters.charAt(q);

            // Update the actual string
            this.s[index] = c;

            // Update segment tree
            update(1, 0, n - 1, index, c);

            // Longest repeating substring
            ans[q] = tree[1].best;
        }

        return ans;
    }

    private void build(int node, int left, int right) {

        // Leaf node
        if (left == right) {
            tree[node] = new Node(s[left]);
            return;
        }

        int mid = (left + right) / 2;

        build(node * 2, left, mid);
        build(node * 2 + 1, mid + 1, right);

        tree[node] = merge(
                tree[node * 2],
                tree[node * 2 + 1]
        );
    }

    private void update(
            int node,
            int left,
            int right,
            int index,
            char c) {

        // Leaf node
        if (left == right) {
            tree[node] = new Node(c);
            return;
        }

        int mid = (left + right) / 2;

        if (index <= mid) {
            update(
                    node * 2,
                    left,
                    mid,
                    index,
                    c
            );
        } else {
            update(
                    node * 2 + 1,
                    mid + 1,
                    right,
                    index,
                    c
            );
        }

        // Recalculate current node
        tree[node] = merge(
                tree[node * 2],
                tree[node * 2 + 1]
        );
    }

    private Node merge(Node a, Node b) {

        Node result = new Node();

        // Total length
        result.length = a.length + b.length;

        // First and last characters
        result.leftChar = a.leftChar;
        result.rightChar = b.rightChar;

        // Initially prefix and suffix come
        // from their respective sides
        result.prefix = a.prefix;
        result.suffix = b.suffix;

        // Best answer is initially from either side
        result.best = Math.max(a.best, b.best);

        // We can join the two sides if the
        // boundary characters are the same
        if (a.rightChar == b.leftChar) {

            // Entire left segment is the same character
            if (a.prefix == a.length) {
                result.prefix = a.length + b.prefix;
            }

            // Entire right segment is the same character
            if (b.suffix == b.length) {
                result.suffix = b.length + a.suffix;
            }

            // Join left suffix + right prefix
            result.best = Math.max(
                    result.best,
                    a.suffix + b.prefix
            );
        }

        return result;
    }
}