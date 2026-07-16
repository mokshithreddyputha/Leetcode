import java.util.Arrays;

class Main {

    public static void main(String[] args) {

        int[] nums = {6, 12, 18, 24, 30};

        Solution obj = new Solution();

        long result = obj.gcdSum(nums);

        System.out.println("GCD Sum = " + result);
    }
}

class Solution {

    public long gcdSum(int[] nums) {

        int n = nums.length;
        int[] prefixGcd = new int[n];

        int mx = 0;

        for (int i = 0; i < n; i++) {
            mx = Math.max(mx, nums[i]);
            prefixGcd[i] = gcd(nums[i], mx);
        }

        Arrays.sort(prefixGcd);

        long sum = 0;
        int left = 0;
        int right = n - 1;

        while (left < right) {
            sum += gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }

        return sum;
    }

    private int gcd(int a, int b) {

        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }

        return a;
    }
}