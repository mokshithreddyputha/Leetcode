class Solution {
public:
    bool sumGame(string num) {

        int n = num.size();
        int half = n / 2;

        int sumDiff = 0;
        int questionDiff = 0;

        for (int i = 0; i < half; i++) {

            if (num[i] == '?') {
                questionDiff++;
            } else {
                sumDiff += num[i] - '0';
            }
        }

        for (int i = half; i < n; i++) {

            if (num[i] == '?') {
                questionDiff--;
            } else {
                sumDiff -= num[i] - '0';
            }
        }

        // If number of ? is odd, Alice gets the final move
        int totalQuestions = 0;

        for (char c : num) {
            if (c == '?') {
                totalQuestions++;
            }
        }

        if (totalQuestions % 2 == 1) {
            return true;
        }

        int maxDifference =
            (abs(questionDiff) / 2) * 9;

        return abs(sumDiff) != maxDifference;
    }
};