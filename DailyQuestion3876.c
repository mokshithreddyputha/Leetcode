#include <stdbool.h>

bool uniformArray(int* nums1, int nums1Size) {

    int minValue = nums1[0];
    bool hasOdd = false;

    for (int i = 0; i < nums1Size; i++) {

        if (nums1[i] < minValue) {
            minValue = nums1[i];
        }

        if (nums1[i] % 2 == 1) {
            hasOdd = true;
        }
    }

    // Minimum is even and there is an odd number
    if (minValue % 2 == 0 && hasOdd) {
        return false;
    }

    return true;
}