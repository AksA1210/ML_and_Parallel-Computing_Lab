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


int searchKey(int *arr, int n, int key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == key) {
            return i; 
        }
    }
    return -1; 
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr = generateRandomArray(n);

    // Calculate the sum of elements and measure the execution time
    clock_t start_sum = clock();
    int sum = sumOfElements(arr, n);
    clock_t end_sum = clock();
    double time_taken_sum = ((double)(end_sum - start_sum)) / CLOCKS_PER_SEC;
    printf("Sum of elements: %d\n", sum);
    printf("Time taken for sum calculation: %lf seconds\n", time_taken_sum);

    // Search
    int key;
    printf("\nEnter the key element to search: ");
    scanf("%d", &key);
    clock_t start_search = clock();
    int index = searchKey(arr, n, key);
    clock_t end_search = clock();
    double time_taken_search = ((double)(end_search - start_search)) / CLOCKS_PER_SEC;
    if (index != -1) {
        printf("Key element found at index: %d\n", index);
    } else {
        printf("Key element not found\n");
    }
    printf("Time taken for search operation: %lf seconds\n", time_taken_search);

    free(arr);

    return 0;
}
