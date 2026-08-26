class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {

        int n = s.length();

        int left = 0;
        int ones = 0;

        int minLength = INT_MAX;
        string answer = "";

        for (int right = 0; right < n; right++) {

            // Add s[right]
            if (s[right] == '1') {
                ones++;
            }

            // More than k ones
            while (ones > k) {

                if (s[left] == '1') {
                    ones--;
                }

                left++;
            }

            // Exactly k ones
            if (ones == k) {

                // Remove unnecessary zeros
                while (s[left] == '0') {
                    left++;
                }

                int length = right - left + 1;

                string current = s.substr(left, length);

                if (length < minLength ||
                    (length == minLength && current < answer)) {

                    minLength = length;
                    answer = current;
                }
            }
        }

        return answer;
    }
};