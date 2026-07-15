class dailyQuestion3658 {

    public static void main(String[] args) {

        int n = 5;

        Solution obj = new Solution();

        int result = obj.gcdOfOddEvenSums(n);

        System.out.println("GCD = " + result);
    }
}

class Solution {

    public int gcdOfOddEvenSums(int n) {

        int a = n * n;
        int b = n * (n + 1);

        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }

        return a;
    }
}