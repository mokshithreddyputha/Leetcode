#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIMIT 1000001LL

int primes[700], pc = 0;

void sieve(int n) {
    int *vis = calloc(n + 1, sizeof(int));

    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            primes[pc++] = i;
            for (int j = i * 2; j <= n; j += i)
                vis[j] = 1;
        }
    }
    free(vis);
}

int expFact(int n, int p) {
    int res = 0;
    while (n) {
        n /= p;
        res += n;
    }
    return res;
}

long long ways(int cnt[26]) {
    int total = 0;
    for (int i = 0; i < 26; i++)
        total += cnt[i];

    long long ans = 1;

    for (int i = 0; i < pc; i++) {
        int p = primes[i];
        int e = expFact(total, p);

        for (int j = 0; j < 26; j++)
            e -= expFact(cnt[j], p);

        while (e--) {
            if (ans > LIMIT / p)
                return LIMIT;
            ans *= p;
        }
    }

    return ans > LIMIT ? LIMIT : ans;
}

char* smallestPalindrome(char* s, int k) {
    static char ans[10005];

    int freq[26] = {0};
    int half[26] = {0};

    int n = strlen(s);

    for (int i = 0; i < n; i++)
        freq[s[i] - 'a']++;

    char mid = 0;
    int halfLen = 0;

    for (int i = 0; i < 26; i++) {
        half[i] = freq[i] / 2;
        halfLen += half[i];
        if (freq[i] & 1)
            mid = 'a' + i;
    }

    sieve(halfLen);

    if (ways(half) < k) {
        ans[0] = '\0';
        return ans;
    }

    int idx = 0;

    for (int pos = 0; pos < halfLen; pos++) {
        for (int c = 0; c < 26; c++) {
            if (!half[c]) continue;

            half[c]--;
            long long cnt = ways(half);

            if (cnt >= k) {
                ans[idx++] = 'a' + c;
                break;
            } else {
                k -= cnt;
                half[c]++;
            }
        }
    }

    if (mid)
        ans[idx++] = mid;

    for (int i = halfLen - 1; i >= 0; i--)
        ans[idx++] = ans[i];

    ans[idx] = '\0';
    return ans;
}