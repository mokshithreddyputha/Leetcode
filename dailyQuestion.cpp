#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int MAXV = 50000;

        vector<long long> freq(MAXV + 1, 0);
        for (int x : nums)
            freq[x]++;

        // cnt[g] = how many numbers are divisible by g
        vector<long long> cnt(MAXV + 1, 0);

        for (int g = 1; g <= MAXV; g++) {
            for (int multiple = g; multiple <= MAXV; multiple += g) {
                cnt[g] += freq[multiple];
            }
        }

        // exactPairs[g] = number of pairs with gcd exactly g
        vector<long long> exactPairs(MAXV + 1, 0);

        for (int g = MAXV; g >= 1; g--) {
            long long pairs = cnt[g] * (cnt[g] - 1) / 2;

            for (int multiple = 2 * g; multiple <= MAXV; multiple += g) {
                pairs -= exactPairs[multiple];
            }

            exactPairs[g] = pairs;
        }

        // Prefix counts of sorted gcdPairs
        vector<long long> prefix(MAXV + 1, 0);

        for (int g = 1; g <= MAXV; g++) {
            prefix[g] = prefix[g - 1] + exactPairs[g];
        }

        vector<int> answer;

        for (long long q : queries) {
            // q is 0-indexed
            long long target = q + 1;

            int left = 1, right = MAXV;
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