#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixGcd(n);

        int mx = 0;

        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            prefixGcd[i] = gcd(nums[i], mx);
        }

        sort(prefixGcd.begin(), prefixGcd.end());

        long long sum = 0;
        int left = 0;
        int right = n - 1;

        while (left < right) {
            sum += gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }

        return sum;
    }
};

int main() {

    vector<int> nums = {6, 12, 18, 24, 30};

    Solution obj;

    long long result = obj.gcdSum(nums);

    cout << "GCD Sum = " << result << endl;

    return 0;
}