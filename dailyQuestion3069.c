int* resultArray(int* nums, int numsSize, int* returnSize) {
    
    int* arr1 = malloc(numsSize * sizeof(int));
    int* arr2 = malloc(numsSize * sizeof(int));

    int j = 1;
    int k = 1;

    arr1[0] = nums[0];
    arr2[0] = nums[1];

    for (int i = 2; i < numsSize; i++) {
        if (arr1[j - 1] > arr2[k - 1])
            arr1[j++] = nums[i];
        else
            arr2[k++] = nums[i];
    }

    *returnSize = j + k;

    int* result = malloc((*returnSize) * sizeof(int));

    for (int i = 0; i < j; i++)
        result[i] = arr1[i];

    for (int i = 0; i < k; i++)
        result[j + i] = arr2[i];

    free(arr1);
    free(arr2);

    return result;
}