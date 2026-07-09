class _14 {

    public static void main(String[] args) {

        String[] strs = {"flower", "flow", "flight"};

        Solution obj = new Solution();

        String result = obj.longestCommonPrefix(strs);

        System.out.println("Longest Common Prefix: " + result);
    }
}

class Solution {

    public String longestCommonPrefix(String[] strs) {

        if (strs == null || strs.length == 0)
            return "";

        String prefix = strs[0];

        for (int i = 0; i < strs.length; i++) {

            while (!strs[i].startsWith(prefix)) {
                prefix = prefix.substring(0, prefix.length() - 1);

                if (prefix.isEmpty())
                    return "";
            }
        }

        return prefix;
    }
}