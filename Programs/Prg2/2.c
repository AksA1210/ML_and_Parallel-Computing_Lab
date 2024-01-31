#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random integer array of size n
int *generateRandomArray(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
    return arr;
}

// Function to find the sum of elements in an array
int sumOfElements(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    return sum;
}

// Function to search a key element in an array
int searchKey(int *arr, int n, int key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == key) {
            return i; // Return index of key if found
        }
    }
    return -1; // Return -1 if key not found
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    // Generate random array
    int *arr = generateRandomArray(n);

    // Calculate the sum of elements and measure the execution time
    clock_t start_sum = clock();
    int sum = sumOfElements(arr, n);
    clock_t end_sum = clock();
    double time_taken_sum = ((double)(end_sum - start_sum)) / CLOCKS_PER_SEC;
    printf("Sum of elements: %d\n", sum);
    printf("Time taken for sum calculation: %lf seconds\n", time_taken_sum);

    // Search a key element and measure the execution time
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

    // Free dynamically allocated memory
    free(arr);

    return 0;
}
