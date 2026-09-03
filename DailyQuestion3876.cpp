class Solution {
public:
    bool uniformArray(vector<int>& nums1) {

        int minValue = nums1[0];
        bool hasOdd = false;

        for (int num : nums1) {

            minValue = min(minValue, num);

            if (num % 2 == 1) {
                hasOdd = true;
            }
        }

        // Minimum is even and an odd number exists
        if (minValue % 2 == 0 && hasOdd) {
            return false;
        }

        return true;
    }
};