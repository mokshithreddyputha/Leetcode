#include <stdio.h>

int gcdOfOddEvenSums(int n) {
    int a = n * n;
    int b = n * (n + 1);

    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

int main() {
    int n = 5;

    int result = gcdOfOddEvenSums(n);

    printf("GCD = %d\n", result);

    return 0;
}