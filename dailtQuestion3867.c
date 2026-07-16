#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

long long gcdSum(int* nums, int numsSize) {

    int *prefixGcd = (int *)malloc(numsSize * sizeof(int));

    int mx = 0;

    // Construct prefixGcd array
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > mx)
            mx = nums[i];

        prefixGcd[i] = gcd(nums[i], mx);
    }

    // Sort prefixGcd
    qsort(prefixGcd, numsSize, sizeof(int), compare);

    long long sum = 0;

    // Pair smallest with largest
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        sum += gcd(prefixGcd[left], prefixGcd[right]);
        left++;
        right--;
    }

    free(prefixGcd);

    return sum;
}

int main() {

    int nums[] = {6, 12, 18, 24, 30};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    long long result = gcdSum(nums, numsSize);

    printf("GCD Sum = %lld\n", result);

    return 0;
}