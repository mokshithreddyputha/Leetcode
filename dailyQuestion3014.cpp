class Solution {
public:
    int minimumPushes(string word) {
        int len = word.length();

        int x = 0, n = 0, count = 0, k = 0;

        if (len > 8) {
            n = len / 8;
            x = len % 8;

            if (n == 1) k = 1;
            if (n == 2) k = 3;
            if (n == 3) k = 6;

            count += k * 8 + x * (n + 1);
        }

        if (len <= 8) {
            count += len;
        }

        return count;
    }
};