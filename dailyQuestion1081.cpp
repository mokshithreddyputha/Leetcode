#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last(26);

        // Store the last occurrence of each character
        for (int i = 0; i < s.size(); i++) {
            last[s[i] - 'a'] = i;
        }

        vector<bool> used(26, false);
        string st;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (used[c - 'a'])
                continue;

            while (!st.empty() &&
                   st.back() > c &&
                   last[st.back() - 'a'] > i) {
                used[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            used[c - 'a'] = true;
        }

        return st;
    }
};

int main() {

    string s = "cbacdcbc";

    Solution obj;

    string result = obj.smallestSubsequence(s);

    cout << "Smallest Subsequence: " << result << endl;

    return 0;
}