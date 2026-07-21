#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {

        int ones = 0;

        for (char c : s) {
            if (c == '1')
                ones++;
        }

        string t = "1" + s + "1";

        vector<pair<char, int>> runs;

        for (int i = 0; i < t.size();) {

            int j = i;

            while (j < t.size() && t[j] == t[i])
                j++;

            runs.push_back({t[i], j - i});

            i = j;
        }

        int ans = ones;

        for (int i = 1; i + 1 < runs.size(); i++) {

            if (runs[i].first == '1') {

                int gain = runs[i - 1].second + runs[i + 1].second;

                ans = max(ans, ones + gain);
            }
        }

        return ans;
    }
};

int main() {

    string s = "11000111";

    Solution obj;

    int result = obj.maxActiveSectionsAfterTrade(s);

    cout << "Maximum Active Sections After Trade: " << result << endl;

    return 0;
}