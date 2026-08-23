#include <stdbool.h>
#include <stdlib.h>

bool sumGame(char* num) {

    int n = 0;

    while (num[n] != '\0') {
        n++;
    }

    int half = n / 2;

    int sumDiff = 0;
    int questionDiff = 0;
    int totalQuestions = 0;

    for (int i = 0; i < half; i++) {

        if (num[i] == '?') {
            questionDiff++;
            totalQuestions++;
        } else {
            sumDiff += num[i] - '0';
        }
    }

    for (int i = half; i < n; i++) {

        if (num[i] == '?') {
            questionDiff--;
            totalQuestions++;
        } else {
            sumDiff -= num[i] - '0';
        }
    }

    // Odd number of ? means Alice gets the last move
    if (totalQuestions % 2 == 1) {
        return true;
    }

    int maxDifference =
        (abs(questionDiff) / 2) * 9;

    return abs(sumDiff) != maxDifference;
}