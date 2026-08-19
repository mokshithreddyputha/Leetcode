class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {

        sort(reservedSeats.begin(), reservedSeats.end());

        long long count = 0;
        int i = 0;
        int reservedRows = 0;

        while (i < reservedSeats.size()) {

            int row = reservedSeats[i][0];
            int mask = 0;

            reservedRows++;

            // Get all reserved seats in this row
            while (i < reservedSeats.size() &&
                   reservedSeats[i][0] == row) {

                int seat = reservedSeats[i][1];

                mask |= (1 << seat);

                i++;
            }

            bool left =
                !(mask & (1 << 2)) &&
                !(mask & (1 << 3)) &&
                !(mask & (1 << 4)) &&
                !(mask & (1 << 5));

            bool middle =
                !(mask & (1 << 4)) &&
                !(mask & (1 << 5)) &&
                !(mask & (1 << 6)) &&
                !(mask & (1 << 7));

            bool right =
                !(mask & (1 << 6)) &&
                !(mask & (1 << 7)) &&
                !(mask & (1 << 8)) &&
                !(mask & (1 << 9));

            if (left && right)
                count += 2;
            else if (left || middle || right)
                count++;
        }

        // Completely empty rows
        count += (long long)(n - reservedRows) * 2;

        return count;
    }
};