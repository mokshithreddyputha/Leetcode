#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    struct State {
        int r;
        int c;
        int mask;
        int energy;
    };

    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        int startR = 0;
        int startC = 0;

        int litterCount = 0;

        // Give every litter cell an ID: 0, 1, 2, ...
        vector<vector<int>> litterId(
            m,
            vector<int>(n, -1)
        );

        // Find S and number the litter cells
        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    startR = i;
                    startC = j;
                }

                if (classroom[i][j] == 'L') {

                    litterId[i][j] = litterCount;
                    litterCount++;
                }
            }
        }

        // No litter
        if (litterCount == 0) {
            return 0;
        }

        int maskCount = 1 << litterCount;

        int allMask = maskCount - 1;

        /*
         * bestEnergy[r][c][mask]
         *
         * Stores the maximum energy with which
         * we have reached (r,c) having this mask.
         *
         * Flattened into 1D array for better performance.
         */
        vector<int> bestEnergy(
            m * n * maskCount,
            -1
        );

        auto getIndex = [&](int r, int c, int mask) {

            return (r * n + c) * maskCount + mask;
        };

        queue<State> q;

        // Starting state
        q.push({
            startR,
            startC,
            0,
            energy
        });

        bestEnergy[
            getIndex(startR, startC, 0)
        ] = energy;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            int size = q.size();

            // Process one BFS level
            while (size--) {

                State cur = q.front();
                q.pop();

                int r = cur.r;
                int c = cur.c;
                int mask = cur.mask;
                int currentEnergy = cur.energy;

                // All litter collected
                if (mask == allMask) {
                    return moves;
                }

                // Cannot move without energy
                if (currentEnergy == 0) {
                    continue;
                }

                for (int d = 0; d < 4; d++) {

                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n) {
                        continue;
                    }

                    // Obstacle
                    if (classroom[nr][nc] == 'X') {
                        continue;
                    }

                    // Moving costs 1 energy
                    int newEnergy = currentEnergy - 1;

                    // Reset energy on R
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    // Update litter mask
                    int newMask = mask;

                    if (litterId[nr][nc] != -1) {

                        int id = litterId[nr][nc];

                        newMask |= (1 << id);
                    }

                    int index =
                        getIndex(nr, nc, newMask);

                    /*
                     * IMPORTANT:
                     *
                     * If we have already reached this
                     * (position + mask) with >= energy,
                     * this new state is useless.
                     */
                    if (bestEnergy[index] >= newEnergy) {
                        continue;
                    }

                    // We found a better state
                    bestEnergy[index] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};