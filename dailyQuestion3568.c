#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int r;
    int c;
    int mask;
    int energy;
} State;


/* Grow the queue when it becomes full */
void pushState(
    State** queue,
    int* back,
    int* capacity,
    State state
) {
    if (*back >= *capacity) {

        *capacity *= 2;

        *queue = realloc(
            *queue,
            (*capacity) * sizeof(State)
        );
    }

    (*queue)[(*back)++] = state;
}


int minMoves(
    char** classroom,
    int classroomSize,
    int energy
) {

    int m = classroomSize;
    int n = strlen(classroom[0]);

    int startR = 0;
    int startC = 0;

    int litterCount = 0;

    /*
     * litterId[r][c]
     *
     * -1 = not litter
     *  0 = first litter
     *  1 = second litter
     * ...
     */
    int** litterId =
        malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {

        litterId[i] =
            malloc(n * sizeof(int));

        for (int j = 0; j < n; j++) {
            litterId[i][j] = -1;
        }
    }


    /*
     * Find S and number all L cells.
     */
    for (int i = 0; i < m; i++) {

        for (int j = 0; j < n; j++) {

            if (classroom[i][j] == 'S') {
                startR = i;
                startC = j;
            }

            if (classroom[i][j] == 'L') {

                litterId[i][j] =
                    litterCount;

                litterCount++;
            }
        }
    }


    /*
     * If there is no litter,
     * answer is immediately 0.
     */
    if (litterCount == 0) {

        for (int i = 0; i < m; i++) {
            free(litterId[i]);
        }

        free(litterId);

        return 0;
    }


    /*
     * Number of possible masks.
     *
     * If there are 3 litter:
     *
     * 000
     * 001
     * 010
     * 011
     * 100
     * 101
     * 110
     * 111
     *
     * = 2^3
     */
    int maskCount =
        1 << litterCount;

    int allMask =
        maskCount - 1;


    /*
     * bestEnergy[r][c][mask]
     *
     * Stores the maximum energy
     * with which we have reached
     * (r,c) with this mask.
     */
    int totalStates =
        m * n * maskCount;

    int* bestEnergy =
        malloc(
            totalStates * sizeof(int)
        );


    for (int i = 0; i < totalStates; i++) {
        bestEnergy[i] = -1;
    }


    /*
     * Convert:
     *
     * (r,c,mask)
     *
     * into one array index.
     */
    #define INDEX(r,c,mask) \
        (((r) * n + (c)) * maskCount + (mask))


    /*
     * Dynamic BFS queue.
     *
     * We cannot assume that every state
     * is inserted only once.
     */
    int capacity = 10000;

    State* queue =
        malloc(
            capacity * sizeof(State)
        );

    int front = 0;
    int back = 0;


    /*
     * Starting state.
     */
    pushState(
        &queue,
        &back,
        &capacity,
        (State){
            startR,
            startC,
            0,
            energy
        }
    );


    bestEnergy[
        INDEX(startR, startC, 0)
    ] = energy;


    int moves = 0;


    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};


    /*
     * BFS
     */
    while (front < back) {

        /*
         * Number of states in this BFS level.
         */
        int levelEnd = back;


        while (front < levelEnd) {

            State current =
                queue[front++];


            int r =
                current.r;

            int c =
                current.c;

            int mask =
                current.mask;

            int currentEnergy =
                current.energy;


            /*
             * IMPORTANT:
             *
             * This state may be stale.
             *
             * Example:
             *
             * We previously inserted
             * (r,c,mask,5)
             *
             * but later found
             * (r,c,mask,10).
             *
             * The old state with energy 5
             * is useless.
             */
            if (
                currentEnergy <
                bestEnergy[
                    INDEX(r, c, mask)
                ]
            ) {
                continue;
            }


            /*
             * All litter collected.
             */
            if (mask == allMask) {

                free(queue);
                free(bestEnergy);

                for (int i = 0; i < m; i++) {
                    free(litterId[i]);
                }

                free(litterId);

                return moves;
            }


            /*
             * No energy means no move.
             */
            if (currentEnergy == 0) {
                continue;
            }


            /*
             * Try four directions.
             */
            for (int d = 0; d < 4; d++) {

                int nr =
                    r + dr[d];

                int nc =
                    c + dc[d];


                /*
                 * Outside grid.
                 */
                if (
                    nr < 0 ||
                    nr >= m ||
                    nc < 0 ||
                    nc >= n
                ) {
                    continue;
                }


                /*
                 * Obstacle.
                 */
                if (
                    classroom[nr][nc] == 'X'
                ) {
                    continue;
                }


                /*
                 * Moving costs 1 energy.
                 */
                int newEnergy =
                    currentEnergy - 1;


                /*
                 * R resets energy.
                 */
                if (
                    classroom[nr][nc] == 'R'
                ) {
                    newEnergy = energy;
                }


                /*
                 * Copy current mask.
                 */
                int newMask =
                    mask;


                /*
                 * If we reached litter,
                 * mark it as collected.
                 */
                if (
                    litterId[nr][nc] != -1
                ) {

                    int id =
                        litterId[nr][nc];

                    newMask |=
                        (1 << id);
                }


                /*
                 * Index for the new state.
                 */
                int index =
                    INDEX(
                        nr,
                        nc,
                        newMask
                    );


                /*
                 * If we already reached
                 * this position with the
                 * same mask and MORE energy,
                 * this state is useless.
                 */
                if (
                    bestEnergy[index]
                    >= newEnergy
                ) {
                    continue;
                }


                /*
                 * This is a better state.
                 */
                bestEnergy[index] =
                    newEnergy;


                /*
                 * Add to BFS queue.
                 */
                pushState(
                    &queue,
                    &back,
                    &capacity,
                    (State){
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    }
                );
            }
        }


        /*
         * Move to next BFS level.
         */
        moves++;
    }


    /*
     * Impossible.
     */
    free(queue);
    free(bestEnergy);

    for (int i = 0; i < m; i++) {
        free(litterId[i]);
    }

    free(litterId);

    return -1;
}