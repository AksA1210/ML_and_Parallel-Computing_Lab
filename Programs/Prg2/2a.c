#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *generateRandomArray(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100; 
    }
    return arr;
}


int sumOfElements(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int n;
    printf("\n----------SEQUENTIAL-----------");
    printf("\nEnter the size of the array : ");
    scanf("%d", &n);

    int *arr = generateRandomArray(n);

    clock_t start_sum = clock();
    int sum = sumOfElements(arr, n);
    clock_t end_sum = clock();
    double time_taken_sum = ((double)(end_sum - start_sum)) / CLOCKS_PER_SEC;
    printf("Sum of elements : %d\n", sum);
    printf("Time taken for sum calculation : %lf seconds\n", time_taken_sum);
    free(arr);

    return 0;
}
