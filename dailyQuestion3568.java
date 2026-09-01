import java.util.*;

class Solution {

    public int minMoves(String[] classroom, int energy) {

        int m = classroom.length;
        int n = classroom[0].length();

        int startR = 0;
        int startC = 0;

        int litterCount = 0;

        // litterId[r][c] tells us which litter this cell represents.
        // -1 means this cell is not litter.
        int[][] litterId = new int[m][n];

        for (int i = 0; i < m; i++) {

            Arrays.fill(litterId[i], -1);

            for (int j = 0; j < n; j++) {

                char ch = classroom[i].charAt(j);

                if (ch == 'S') {
                    startR = i;
                    startC = j;
                }

                if (ch == 'L') {
                    litterId[i][j] = litterCount;
                    litterCount++;
                }
            }
        }

        // No litter to collect
        if (litterCount == 0) {
            return 0;
        }

        // Example:
        // 3 litter -> 111 -> 7
        int allMask = (1 << litterCount) - 1;

        /*
         * visited[row][col][mask][energy]
         */
        boolean[][][][] visited =
            new boolean[m][n][1 << litterCount][energy + 1];

        /*
         * State:
         * [0] = row
         * [1] = column
         * [2] = collected litter mask
         * [3] = remaining energy
         */
        Queue<int[]> queue = new LinkedList<>();

        queue.offer(new int[] {
            startR,
            startC,
            0,
            energy
        });

        visited[startR][startC][0][energy] = true;

        int moves = 0;

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        while (!queue.isEmpty()) {

            int size = queue.size();

            // Process all states requiring 'moves' moves
            for (int q = 0; q < size; q++) {

                int[] state = queue.poll();

                int r = state[0];
                int c = state[1];
                int mask = state[2];
                int currentEnergy = state[3];

                // All litter collected
                if (mask == allMask) {
                    return moves;
                }

                // Cannot move if energy is 0
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
                    if (classroom[nr].charAt(nc) == 'X') {
                        continue;
                    }

                    // Moving costs 1 energy
                    int newEnergy = currentEnergy - 1;

                    // Reset energy if we land on R
                    if (classroom[nr].charAt(nc) == 'R') {
                        newEnergy = energy;
                    }

                    // Update litter mask
                    int newMask = mask;

                    if (litterId[nr][nc] != -1) {

                        int id = litterId[nr][nc];

                        newMask = mask | (1 << id);
                    }

                    // Already visited this exact state
                    if (visited[nr][nc][newMask][newEnergy]) {
                        continue;
                    }

                    visited[nr][nc][newMask][newEnergy] = true;

                    queue.offer(new int[] {
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
}