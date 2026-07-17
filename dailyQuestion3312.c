#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int cmpLongLong(const void *a, const void *b) {
    long long x = *(long long *)a;
    long long y = *(long long *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int* gcdValues(int* nums, int numsSize, long long* queries,
               int queriesSize, int* returnSize) {

    int MAX = 50000;

    long long *freq = calloc(MAX + 1, sizeof(long long));

    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // divisible[g] = count of numbers divisible by g
    long long *divisible = calloc(MAX + 1, sizeof(long long));

    for (int g = 1; g <= MAX; g++) {
        for (int multiple = g; multiple <= MAX; multiple += g) {
            divisible[g] += freq[multiple];
        }
    }

    // exactPairs[g] = number of pairs with gcd exactly g
    long long *exactPairs = calloc(MAX + 1, sizeof(long long));

    for (int g = MAX; g >= 1; g--) {

        long long pairs =
            divisible[g] * (divisible[g] - 1) / 2;

        for (int multiple = 2 * g;
             multiple <= MAX;
             multiple += g) {

            pairs -= exactPairs[multiple];
        }

        exactPairs[g] = pairs;
    }

    // prefix[g] = count of gcd values <= g
    long long *prefix = calloc(MAX + 1, sizeof(long long));

    for (int g = 1; g <= MAX; g++) {
        prefix[g] = prefix[g - 1] + exactPairs[g];
    }

    int *answer = malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {

        long long target = queries[i] + 1;

        int left = 1;
        int right = MAX;

        while (left < right) {

            int mid = left + (right - left) / 2;

            if (prefix[mid] >= target)
                right = mid;
            else
                left = mid + 1;
        }

        answer[i] = left;
    }

    free(freq);
    free(divisible);
    free(exactPairs);
    free(prefix);

    *returnSize = queriesSize;

    return answer;
}

int main() {

    int nums[] = {2, 3, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    long long queries[] = {0, 1, 2};
    int queriesSize = sizeof(queries) / sizeof(queries[0]);

    int returnSize;

    int *result = gcdValues(
        nums,
        numsSize,
        queries,
        queriesSize,
        &returnSize
    );

    printf("Answer: ");

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }

    printf("\n");

    free(result);

    return 0;
}