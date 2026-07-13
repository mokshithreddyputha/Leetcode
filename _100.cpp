#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {

        queue<TreeNode*> qp, qq;
        qp.push(p);
        qq.push(q);

        while (!qp.empty() && !qq.empty()) {

            TreeNode* a = qp.front();
            qp.pop();

            TreeNode* b = qq.front();
            qq.pop();

            if (a == nullptr && b == nullptr)
                continue;

            if (a == nullptr || b == nullptr)
                return false;

            if (a->val != b->val)
                return false;

            qp.push(a->left);
            qp.push(a->right);

            qq.push(b->left);
            qq.push(b->right);
        }

        return qp.empty() && qq.empty();
    }
};

int main() {

    // Tree 1: [1,2,3]
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    // Tree 2: [1,2,3]
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    Solution obj;

    if (obj.isSameTree(p, q))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}