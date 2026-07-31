#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Descending order
}

int minimumPushes(char *word) {
    int freq[26] = {0};

    for (int i = 0; word[i] != '\0'; i++) {
        freq[word[i] - 'a']++;
    }

    qsort(freq, 26, sizeof(int), compare);

    int ans = 0;

    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0)
            break;

        int cost = i / 8 + 1;
        ans += freq[i] * cost;
    }

    return ans;
}

int main() {
    char word[] = "aabbccddeeffgghhiiiiii";
    printf("%d\n", minimumPushes(word));
    return 0;
}