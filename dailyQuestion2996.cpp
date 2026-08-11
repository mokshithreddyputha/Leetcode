class Solution {
public:
    int missingInteger(vector<int>& nums) {

        int sum = nums[0];

        // Find longest sequential prefix
        int i = 1;

        while (i < nums.size() &&
               nums[i] == nums[i - 1] + 1) {

            sum += nums[i];
            i++;
        }

        // Store all numbers
        unordered_set<int> st;

        for (int num : nums) {
            st.insert(num);
        }

        // Find smallest missing number >= sum
        while (st.count(sum)) {
            sum++;
        }

        return sum;
    }
};