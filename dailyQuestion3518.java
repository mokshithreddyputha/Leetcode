import java.util.*;

class Solution {
    static final long LIMIT = 1000001;
    List<Integer> primes = new ArrayList<>();

    void sieve(int n) {
        boolean[] vis = new boolean[n + 1];
        for (int i = 2; i <= n; i++) {
            if (!vis[i]) {
                primes.add(i);
                for (int j = i * 2; j <= n; j += i)
                    vis[j] = true;
            }
        }
    }

    int expFact(int n, int p) {
        int res = 0;
        while (n > 0) {
            n /= p;
            res += n;
        }
        return res;
    }

    long ways(int[] cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long ans = 1;

        for (int p : primes) {
            int e = expFact(total, p);
            for (int c : cnt)
                e -= expFact(c, p);

            while (e-- > 0) {
                if (ans > LIMIT / p) return LIMIT;
                ans *= p;
            }
        }
        return Math.min(ans, LIMIT);
    }

    public String kthPalindrome(String s, int k) {
        int[] freq = new int[26];
        for (char c : s.toCharArray())
            freq[c - 'a']++;

        int[] half = new int[26];
        int halfLen = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            halfLen += half[i];
            if ((freq[i] & 1) == 1)
                mid = (char) ('a' + i);
        }

        sieve(halfLen);

        if (ways(half) < k) return "";

        StringBuilder left = new StringBuilder();

        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                long cnt = ways(half);

                if (cnt >= k) {
                    left.append((char) ('a' + c));
                    break;
                } else {
                    k -= cnt;
                    half[c]++;
                }
            }
        }

        StringBuilder ans = new StringBuilder(left);
        if (mid != 0) ans.append(mid);
        ans.append(new StringBuilder(left).reverse());

        return ans.toString();
    }
}