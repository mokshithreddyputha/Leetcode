import java.util.*;

class Solution {
    public int missingInteger(int[] nums) {

        int sum = nums[0];

        // Find longest sequential prefix
        int i = 1;

        while (i < nums.length && nums[i] == nums[i - 1] + 1) {
            sum += nums[i];
            i++;
        }

        // Store all numbers
        HashSet<Integer> set = new HashSet<>();

        for (int num : nums) {
            set.add(num);
        }

        // Find smallest missing number >= sum
        while (set.contains(sum)) {
            sum++;
        }

        return sum;
    }
}