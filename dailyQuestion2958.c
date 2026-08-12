#include <stdlib.h>

typedef struct Node {
    int key;
    int count;
    struct Node* next;
} Node;

#define SIZE 200003

int hash(int key) {
    return key % SIZE;
}

int maxSubarrayLength(int* nums, int numsSize, int k) {

    Node* table[SIZE] = {NULL};

    int left = 0;
    int maxLength = 0;

    for (int right = 0; right < numsSize; right++) {

        int h = hash(nums[right]);

        Node* cur = table[h];

        while (cur != NULL && cur->key != nums[right])
            cur = cur->next;

        if (cur == NULL) {
            cur = (Node*)malloc(sizeof(Node));
            cur->key = nums[right];
            cur->count = 0;
            cur->next = table[h];
            table[h] = cur;
        }

        cur->count++;

        // Find frequency of nums[right]
        while (cur->count > k) {

            int lh = hash(nums[left]);

            Node* temp = table[lh];

            while (temp != NULL && temp->key != nums[left])
                temp = temp->next;

            temp->count--;

            left++;

            // Recalculate current element frequency
            h = hash(nums[right]);
            cur = table[h];

            while (cur != NULL && cur->key != nums[right])
                cur = cur->next;
        }

        int length = right - left + 1;

        if (length > maxLength)
            maxLength = length;
    }

    return maxLength;
}