import java.util.*;

class Main {

    public static void main(String[] args) {

        int[] nums = {2, 3, 4};
        long[] queries = {0, 1, 2};

        Solution obj = new Solution();

        int[] result = obj.gcdValues(nums, queries);

        System.out.println("Answer: " + Arrays.toString(result));
    }
}

class Solution {

    public int[] gcdValues(int[] nums, long[] queries) {

        int MAX = 50000;

        long[] freq = new long[MAX + 1];

        for (int x : nums) {
            freq[x]++;
        }

        // divisible[g] = count of numbers divisible by g
        long[] divisible = new long[MAX + 1];

        for (int g = 1; g <= MAX; g++) {
            for (int multiple = g; multiple <= MAX; multiple += g) {
                divisible[g] += freq[multiple];
            }
        }

        // exactPairs[g] = number of pairs having gcd exactly g
        long[] exactPairs = new long[MAX + 1];

        for (int g = MAX; g >= 1; g--) {

            long pairs = divisible[g] * (divisible[g] - 1) / 2;

            for (int multiple = 2 * g; multiple <= MAX; multiple += g) {
                pairs -= exactPairs[multiple];
            }

            exactPairs[g] = pairs;
        }

        // prefix[g] = number of gcd values <= g
        long[] prefix = new long[MAX + 1];

        for (int g = 1; g <= MAX; g++) {
            prefix[g] = prefix[g - 1] + exactPairs[g];
        }

        int[] answer = new int[queries.length];

        for (int i = 0; i < queries.length; i++) {

            long target = queries[i] + 1; // convert to 1-based index

            int left = 1;
            int right = MAX;

            while (left < right) {

                int mid = left + (right - left) / 2;

                if (prefix[mid] >= target) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }

            answer[i] = left;
        }

        return answer;
    }
}