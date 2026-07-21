#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int maxActiveSectionsAfterTrade(char* s) {

    int ones = 0;
    int n = strlen(s);

    for (int i = 0; i < n; i++) {
        if (s[i] == '1')
            ones++;
    }

    char *t = (char *)malloc(n + 3);

    t[0] = '1';
    strcpy(t + 1, s);
    t[n + 1] = '1';
    t[n + 2] = '\0';

    int len = n + 2;

    char *type = (char *)malloc((len + 1) * sizeof(char));
    int *cnt = (int *)malloc((len + 1) * sizeof(int));

    int runs = 0;

    for (int i = 0; i < len;) {

        int j = i;

        while (j < len && t[j] == t[i])
            j++;

        type[runs] = t[i];
        cnt[runs] = j - i;
        runs++;

        i = j;
    }

    int ans = ones;

    for (int i = 1; i + 1 < runs; i++) {

        if (type[i] == '1') {

            int gain = cnt[i - 1] + cnt[i + 1];

            ans = max(ans, ones + gain);
        }
    }

    free(t);
    free(type);
    free(cnt);

    return ans;
}

int main() {

    char s[] = "11000111";

    int result = maxActiveSectionsAfterTrade(s);

    printf("Maximum Active Sections After Trade: %d\n", result);

    return 0;
}