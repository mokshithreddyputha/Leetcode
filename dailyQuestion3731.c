/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

int* missingInteger(int* nums, int numsSize, int* returnSize) {
    int min = nums[0], max = nums[0];

    bool present[101] = {false};

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < min) min = nums[i];
        if (nums[i] > max) max = nums[i];
        present[nums[i]] = true;
    }

    int* ans = (int*)malloc(101 * sizeof(int));
    int k = 0;

    for (int i = min; i <= max; i++) {
        if (!present[i]) {
            ans[k++] = i;
        }
    }

    *returnSize = k;
    return ans;
}