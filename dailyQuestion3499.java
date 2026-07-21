import java.util.*;

class Main {

    public static void main(String[] args) {

        String s = "11000111";

        Solution obj = new Solution();

        int result = obj.maxActiveSectionsAfterTrade(s);

        System.out.println("Maximum Active Sections After Trade: " + result);
    }
}

class Solution {

    public int maxActiveSectionsAfterTrade(String s) {

        int ones = 0;

        for (char c : s.toCharArray()) {
            if (c == '1') {
                ones++;
            }
        }

        String t = "1" + s + "1";

        ArrayList<int[]> runs = new ArrayList<>();

        for (int i = 0; i < t.length();) {

            int j = i;

            while (j < t.length() && t.charAt(j) == t.charAt(i)) {
                j++;
            }

            runs.add(new int[]{t.charAt(i), j - i});

            i = j;
        }

        int ans = ones;

        for (int i = 1; i + 1 < runs.size(); i++) {

            if (runs.get(i)[0] == '1') {

                int gain = runs.get(i - 1)[1] + runs.get(i + 1)[1];

                ans = Math.max(ans, ones + gain);
            }
        }

        return ans;
    }
}