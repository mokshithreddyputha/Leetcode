import java.util.*;

class Solution {
    public int[] validSequence(String word1, String word2) {

        int n = word1.length();
        int m = word2.length();

        int[] ans = new int[m];

        // last[j] = last index in word1
        // that can match word2[j]
        int[] last = new int[m];
        Arrays.fill(last, -1);

        int i = n - 1;
        int j = m - 1;

        // Build last[]
        while (i >= 0 && j >= 0) {
            if (word1.charAt(i) == word2.charAt(j)) {
                last[j] = i;
                j--;
            }
            i--;
        }

        // We can use at most one mismatch
        boolean canSkip = true;

        j = 0;

        for (i = 0; i < n; i++) {

            if (j == m)
                break;

            // Exact match
            if (word1.charAt(i) == word2.charAt(j)) {
                ans[j] = i;
                j++;
            }

            // Use the one allowed mismatch
            else if (canSkip &&
                    (j == m - 1 || i < last[j + 1])) {

                canSkip = false;
                ans[j] = i;
                j++;
            }
        }

        // Could not match all characters
        if (j != m)
            return new int[0];

        return ans;
    }
}