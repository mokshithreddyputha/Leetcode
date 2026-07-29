class Solution {
public:
    const long long LIMIT = 1000001;
    vector<int> primes;

    void sieve(int n) {
        vector<bool> vis(n + 1, false);
        for (int i = 2; i <= n; i++) {
            if (!vis[i]) {
                primes.push_back(i);
                for (int j = i * 2; j <= n; j += i)
                    vis[j] = true;
            }
        }
    }

    int expFact(int n, int p) {
        int res = 0;
        while (n) {
            n /= p;
            res += n;
        }
        return res;
    }

    long long ways(vector<int>& cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ans = 1;

        for (int p : primes) {
            int e = expFact(total, p);
            for (int c : cnt)
                e -= expFact(c, p);

            while (e--) {
                if (ans > LIMIT / p) return LIMIT;
                ans *= p;
            }
        }
        return min(ans, LIMIT);
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26), half(26);

        for (char c : s) freq[c - 'a']++;

        int halfLen = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            halfLen += half[i];
            if (freq[i] & 1) mid = char('a' + i);
        }

        sieve(halfLen);

        if (ways(half) < k) return "";

        string left;

        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (!half[c]) continue;

                half[c]--;
                long long cnt = ways(half);

                if (cnt >= k) {
                    left.push_back(char('a' + c));
                    break;
                } else {
                    k -= cnt;
                    half[c]++;
                }
            }
        }

        string ans = left;
        if (mid) ans.push_back(mid);

        string rev = left;
        reverse(rev.begin(), rev.end());

        ans += rev;
        return ans;
    }
};