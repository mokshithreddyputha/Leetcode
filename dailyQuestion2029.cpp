class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {

        int count[3] = {0, 0, 0};

        // Count remainders
        for (int stone : stones) {
            count[stone % 3]++;
        }

        // Even number of 0-modulo stones
        if (count[0] % 2 == 0) {
            return count[1] > 0 && count[2] > 0;
        }

        // Odd number of 0-modulo stones
        return abs(count[1] - count[2]) > 2;
    }
};