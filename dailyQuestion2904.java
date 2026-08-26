class Solution {
    public String shortestBeautifulSubstring(String s, int k) {

        int n = s.length();

        int left = 0;
        int ones = 0;

        int minLength = Integer.MAX_VALUE;
        String answer = "";

        for (int right = 0; right < n; right++) {

            // Add s[right]
            if (s.charAt(right) == '1') {
                ones++;
            }

            // We have more than k ones
            while (ones > k) {

                if (s.charAt(left) == '1') {
                    ones--;
                }

                left++;
            }

            // We have exactly k ones
            if (ones == k) {

                // Remove unnecessary leading zeros
                while (s.charAt(left) == '0') {
                    left++;
                }

                int length = right - left + 1;

                String current = s.substring(left, right + 1);

                // Better if:
                // 1. It is shorter
                // 2. Same length but lexicographically smaller
                if (length < minLength ||
                    (length == minLength && current.compareTo(answer) < 0)) {

                    minLength = length;
                    answer = current;
                }
            }
        }

        return answer;
    }
}