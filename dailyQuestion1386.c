#include <stdlib.h>

int compare(const void *a, const void *b) {
    int *x = *(int **)a;
    int *y = *(int **)b;

    return x[0] - y[0];
}

int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize,
                        int* reservedSeatsColSize) {

    qsort(reservedSeats, reservedSeatsSize, sizeof(int*), compare);

    long long count = 0;
    int i = 0;

    while (i < reservedSeatsSize) {

        int row = reservedSeats[i][0];
        int mask = 0;

        // Collect all reserved seats of this row
        while (i < reservedSeatsSize && reservedSeats[i][0] == row) {
            int seat = reservedSeats[i][1];
            mask |= (1 << seat);
            i++;
        }

        int left =
            !(mask & (1 << 2)) &&
            !(mask & (1 << 3)) &&
            !(mask & (1 << 4)) &&
            !(mask & (1 << 5));

        int middle =
            !(mask & (1 << 4)) &&
            !(mask & (1 << 5)) &&
            !(mask & (1 << 6)) &&
            !(mask & (1 << 7));

        int right =
            !(mask & (1 << 6)) &&
            !(mask & (1 << 7)) &&
            !(mask & (1 << 8)) &&
            !(mask & (1 << 9));

        if (left && right)
            count += 2;
        else if (left || middle || right)
            count += 1;
        else
            count += 0;
    }

    // Rows with no reserved seats can fit 2 families
    int reservedRows = 0;
    i = 0;

    while (i < reservedSeatsSize) {
        reservedRows++;
        int row = reservedSeats[i][0];

        while (i < reservedSeatsSize && reservedSeats[i][0] == row)
            i++;
    }

    count += (long long)(n - reservedRows) * 2;

    return (int)count;
}