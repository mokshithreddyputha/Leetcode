class Solution {
    public boolean sumGame(String num) {

        int n = num.length();
        int half = n / 2;

        int sumDiff = 0;
        int questionDiff = 0;

        for (int i = 0; i < half; i++) {

            if (num.charAt(i) == '?') {
                questionDiff++;
            } else {
                sumDiff += num.charAt(i) - '0';
            }
        }

        for (int i = half; i < n; i++) {

            if (num.charAt(i) == '?') {
                questionDiff--;
            } else {
                sumDiff -= num.charAt(i) - '0';
            }
        }

        /*
         * Bob can win only when:
         *
         * question marks are balanced in a way that
         * allows the remaining sum difference to be zero.
         */
        return sumDiff != -questionDiff * 9 / 2;
    }
}