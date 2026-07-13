import java.util.*;

class dailyQuestion1291 {

    public static void main(String[] args) {

        int low = 100;
        int high = 13000;

        Solution obj = new Solution();

        List<Integer> result = obj.sequentialDigits(low, high);

        System.out.println(result);
    }
}

class Solution {

    public List<Integer> sequentialDigits(int low, int high) {

        List<Integer> result = new ArrayList<>();
        String digits = "123456789";

        for (int len = 2; len <= 9; len++) {

            for (int start = 0; start + len <= 9; start++) {

                int num = Integer.parseInt(
                        digits.substring(start, start + len)
                );

                if (num >= low && num <= high) {
                    result.add(num);
                }
            }
        }

        return result;
    }
}