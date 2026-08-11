#include <stdlib.h>
#include <stdbool.h>

int missingInteger(int* nums, int numsSize) {

    int sum = nums[0];

    // Find longest sequential prefix
    int i = 1;

    while (i < numsSize &&
           nums[i] == nums[i - 1] + 1) {

        sum += nums[i];
        i++;
    }

    // nums[i] <= 50, so we can use a boolean array
    bool present[101] = {false};

    for (int i = 0; i < numsSize; i++) {
        present[nums[i]] = true;
    }

    // Find smallest missing number >= sum
    while (sum <= 100 && present[sum]) {
        sum++;
    }

    return sum;
}