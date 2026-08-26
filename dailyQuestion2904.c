#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

char* shortestBeautifulSubstring(char* s, int k) {

    int n = strlen(s);

    int left = 0;
    int ones = 0;

    int minLength = INT_MAX;

    char* answer = malloc((n + 1) * sizeof(char));
    answer[0] = '\0';

    for (int right = 0; right < n; right++) {

        if (s[right] == '1') {
            ones++;
        }

        // More than k ones
        while (ones > k) {

            if (s[left] == '1') {
                ones--;
            }

            left++;
        }

        // Exactly k ones
        if (ones == k) {

            // Remove unnecessary leading zeros
            while (s[left] == '0') {
                left++;
            }

            int length = right - left + 1;

            char* current = malloc((length + 1) * sizeof(char));

            strncpy(current, s + left, length);
            current[length] = '\0';

            if (length < minLength ||
                (length == minLength &&
                 strcmp(current, answer) < 0)) {

                minLength = length;
                strcpy(answer, current);
            }

            free(current);
        }
    }

    return answer;
}