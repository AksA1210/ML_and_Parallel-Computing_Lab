#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 10

// Struct to hold arguments for thread functions
typedef struct {
    int *arr;
    int size;
    int result; // For sum operation or index for search operation
    int key;    // For search operation
} ThreadArgs;

// Function prototypes
void *sumThread(void *arg);
void *searchThread(void *arg);
void generateRandomArray(int *arr, int size);
double measureExecutionTime(struct timespec start, struct timespec end);

int main() {
    int N_values[] = {100, 500, 1000, 2000, 5000, 10000};
    int num_threads;
    struct timespec start_time, end_time;
    double execution_time;

    // Loop through different array sizes
    for (int i = 0; i < sizeof(N_values) / sizeof(N_values[0]); i++) {
        int N = N_values[i];
        int *arr = (int *)malloc(N * sizeof(int));
        generateRandomArray(arr, N);

        // Loop through different number of threads
        for (num_threads = 1; num_threads <= MAX_THREADS; num_threads++) {
            pthread_t threads[num_threads];
            ThreadArgs args[num_threads];

            // Measure start time
            clock_gettime(CLOCK_MONOTONIC, &start_time);

            // Create threads for sum operation
            for (int j = 0; j < num_threads; j++) {
                args[j].arr = arr;
                args[j].size = N;
                pthread_create(&threads[j], NULL, sumThread, &args[j]);
            }

            // Join threads for sum operation
            for (int j = 0; j < num_threads; j++) {
                pthread_join(threads[j], NULL);
            }

            // Calculate total sum from individual thread results
            int total_sum = 0;
            for (int j = 0; j < num_threads; j++) {
                total_sum += args[j].result;
            }

            // Measure end time
            clock_gettime(CLOCK_MONOTONIC, &end_time);

            // Calculate execution time
            execution_time = measureExecutionTime(start_time, end_time);

            // Print execution time for sum operation
            printf("Array size: %d, Threads: %d, Sum: %d, Execution time: %lf seconds\n", N, num_threads, total_sum, execution_time);

            // Measure start time for search operation
            clock_gettime(CLOCK_MONOTONIC, &start_time);

            // Create threads for search operation
            for (int j = 0; j < num_threads; j++) {
                args[j].key = rand() % 100; // Generate a random key
                pthread_create(&threads[j], NULL, searchThread, &args[j]);
            }

            // Join threads for search operation
            for (int j = 0; j < num_threads; j++) {
                pthread_join(threads[j], NULL);
            }

            // Measure end time for search operation
            clock_gettime(CLOCK_MONOTONIC, &end_time);

            // Calculate execution time for search operation
            execution_time = measureExecutionTime(start_time, end_time);

            // Print execution time for search operation
            printf("Array size: %d, Threads: %d, Key found at index: %d, Execution time: %lf seconds\n", N, num_threads, args[0].result, execution_time);
        }

        free(arr);
    }

    return 0;
}

// Function to perform sum operation in a thread
void *sumThread(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int sum = 0;
    for (int i = 0; i < args->size; i++) {
        sum += args->arr[i];
    }
    args->result = sum;
    pthread_exit(NULL);
}

// Function to perform search operation in a thread
void *searchThread(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int key = args->key;
    for (int i = 0; i < args->size; i++) {
        if (args->arr[i] == key) {
            args->result = i;
            pthread_exit(NULL);
        }
    }
    args->result = -1; // If key not found
    pthread_exit(NULL);
}

// Function to generate a random integer array
void generateRandomArray(int *arr, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
}

// Function to measure execution time
double measureExecutionTime(struct timespec start, struct timespec end) {
    double start_sec = (double)start.tv_sec * 1.0e9 + (double)start.tv_nsec;
    double end_sec = (double)end.tv_sec * 1.0e9 + (double)end.tv_nsec;
    return (end_sec - start_sec) / 1.0e9; // Convert nanoseconds to seconds
}
