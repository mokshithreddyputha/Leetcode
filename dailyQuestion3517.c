#include <string.h>
#include <stdlib.h>

char* smallestPalindrome(char* s) {
    int freq[26] = {0};
    int n = strlen(s);

    for (int i = 0; i < n; i++)
        freq[s[i] - 'a']++;

    char *ans = (char *)malloc(n + 1);

    int idx = 0;

    // First half
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < freq[i] / 2; j++) {
            ans[idx++] = 'a' + i;
        }
    }

    int firstHalfLen = idx;

    // Middle character
    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2) {
            ans[idx++] = 'a' + i;
            break;
        }
    }

    // Second half (reverse of first half)
    for (int i = firstHalfLen - 1; i >= 0; i--) {
        ans[idx++] = ans[i];
    }

    ans[idx] = '\0';
    return ans;
}