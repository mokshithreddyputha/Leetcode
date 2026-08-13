class Solution {
    
    struct Node {
        char leftChar;
        char rightChar;
        
        int prefix;
        int suffix;
        int best;
        int length;
        
        Node() {}
        
        Node(char c) {
            leftChar = c;
            rightChar = c;
            prefix = 1;
            suffix = 1;
            best = 1;
            length = 1;
        }
    };
    
    vector<Node> tree;
    string s;
    
    Node merge(Node a, Node b) {
        
        Node result;
        
        result.length = a.length + b.length;
        
        result.leftChar = a.leftChar;
        result.rightChar = b.rightChar;
        
        result.prefix = a.prefix;
        result.suffix = b.suffix;
        
        result.best = max(a.best, b.best);
        
        // If boundary characters are same,
        // we can join the two segments.
        if (a.rightChar == b.leftChar) {
            
            // Entire left segment has same character
            if (a.prefix == a.length) {
                result.prefix = a.length + b.prefix;
            }
            
            // Entire right segment has same character
            if (b.suffix == b.length) {
                result.suffix = b.length + a.suffix;
            }
            
            // Join suffix of left + prefix of right
            result.best = max(
                result.best,
                a.suffix + b.prefix
            );
        }
        
        return result;
    }
    
    void build(int node, int left, int right) {
        
        if (left == right) {
            tree[node] = Node(s[left]);
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
    
    void update(
        int node,
        int left,
        int right,
        int index,
        char c
    ) {
        
        if (left == right) {
            tree[node] = Node(c);
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
        
        tree[node] = merge(
            tree[node * 2],
            tree[node * 2 + 1]
        );
    }
    
public:
    
    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        
        this->s = s;
        
        int n = s.length();
        
        tree.resize(4 * n);
        
        // Build initial segment tree
        build(1, 0, n - 1);
        
        vector<int> ans(queryIndices.size());
        
        for (int i = 0; i < queryIndices.size(); i++) {
            
            int index = queryIndices[i];
            char c = queryCharacters[i];
            
            // Update string
            this->s[index] = c;
            
            // Update segment tree
            update(
                1,
                0,
                n - 1,
                index,
                c
            );
            
            // Root contains answer for entire string
            ans[i] = tree[1].best;
        }
        
        return ans;
    }
};