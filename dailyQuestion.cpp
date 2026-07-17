#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {

        const int MAXV = 50000;

        vector<long long> freq(MAXV + 1, 0);

        for (int x : nums)
            freq[x]++;

        // cnt[g] = count of numbers divisible by g
        vector<long long> cnt(MAXV + 1, 0);

        for (int g = 1; g <= MAXV; g++) {
            for (int multiple = g; multiple <= MAXV; multiple += g) {
                cnt[g] += freq[multiple];
            }
        }

        // exactPairs[g] = pairs with gcd exactly g
        vector<long long> exactPairs(MAXV + 1, 0);

        for (int g = MAXV; g >= 1; g--) {

            long long pairs = cnt[g] * (cnt[g] - 1) / 2;

            for (int multiple = 2 * g; multiple <= MAXV; multiple += g) {
                pairs -= exactPairs[multiple];
            }

            exactPairs[g] = pairs;
        }

        // Prefix sums of sorted gcd pairs
        vector<long long> prefix(MAXV + 1, 0);

        for (int g = 1; g <= MAXV; g++) {
            prefix[g] = prefix[g - 1] + exactPairs[g];
        }

        vector<int> answer;

        for (long long q : queries) {

            long long target = q + 1; // queries are 0-indexed

            int left = 1;
            int right = MAXV;

            while (left < right) {

                int mid = left + (right - left) / 2;

                if (prefix[mid] >= target)
                    right = mid;
                else
                    left = mid + 1;
            }

            answer.push_back(left);
        }

        return answer;
    }
};

int main() {

    vector<int> nums = {2, 3, 4};

    vector<long long> queries = {0, 1, 2};

    Solution obj;

    vector<int> result = obj.gcdValues(nums, queries);

    cout << "Answer: ";

    for (int x : result) {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}