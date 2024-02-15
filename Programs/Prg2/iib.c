#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 5

typedef struct {
    int *arr;
    int size;
    int result;
} ThreadArgs;

void *sumThread(void *arg);
void generateRandomArray(int *arr, int size);
double measureExecutionTime(struct timespec start, struct timespec end);
void print_table(int rows,double execution_times[][MAX_THREADS]);
int main() {
    int N_values[] = {100, 1000, 5000, 10000};
    int num_threads;
    struct timespec start_time, end_time;
    double execution_times[sizeof(N_values)/sizeof(N_values[0])][MAX_THREADS];

    for (int i = 0; i < sizeof(N_values) / sizeof(N_values[0]); i++) {
        int N = N_values[i];
        int *arr = (int *)malloc(N * sizeof(int));
        generateRandomArray(arr, N);

        for (num_threads = 1; num_threads <= MAX_THREADS; num_threads++) {
            pthread_t threads[num_threads];
            ThreadArgs args[num_threads];

            clock_gettime(CLOCK_MONOTONIC, &start_time);

            for (int j = 0; j < num_threads; j++) {
                args[j].arr = arr;
                args[j].size = N;
                pthread_create(&threads[j], NULL, sumThread, &args[j]);
            }

            for (int j = 0; j < num_threads; j++) {
                pthread_join(threads[j], NULL);
            }

            clock_gettime(CLOCK_MONOTONIC, &end_time);
            
            execution_times[i][num_threads-1] = measureExecutionTime(start_time, end_time);
        }

        free(arr); 
    }

    print_table(sizeof(N_values) / sizeof(N_values[0]), execution_times);
    return 0;
}

void *sumThread(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int sum = 0;
    for (int i = 0; i < args->size; i++) {
        sum += args->arr[i];
    }
    args->result = sum;
    pthread_exit(NULL);
}

void generateRandomArray(int *arr, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; 
    }
}


double measureExecutionTime(struct timespec start, struct timespec end) {
    double start_sec = (double)start.tv_sec * 1.0e9 + (double)start.tv_nsec;
    double end_sec = (double)end.tv_sec * 1.0e9 + (double)end.tv_nsec;
    return (end_sec - start_sec) / 1.0e9; // Convert nanoseconds to seconds
}


void print_table(int rows,double execution_times[][MAX_THREADS]) {
    // Header
    printf("%-15s%-10s%-10s%-10s%-10s%-10s\n", "Count\\Threads", "1", "2", "3", "4", "5");
    // Separator
    printf("------------------------------------------------------------------\n");

    // Data
    for (int i = 0; i < rows ; i++) {
        printf("%-15d", 100 * (i + 1));
        for (int j = 0; j < MAX_THREADS; j++) {
            printf("%-10.6lf", execution_times[i][j]); 
        }
        printf("\n");
    }
}
