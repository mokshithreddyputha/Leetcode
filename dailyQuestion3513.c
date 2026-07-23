int uniqueXorTriplets(int* nums, int numsSize) {
    if (numsSize < 3)
        return numsSize;

    int bits = 0;
    int n = numsSize;

    while (n > 0) {
        bits++;
        n >>= 1;
    }

    return 1 << bits;
}