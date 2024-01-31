#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to print first n natural numbers
void *printNaturalNumbers(void *arg) {
    int n = *((int *)arg);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", i);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Create a thread
    pthread_t tid;
    pthread_create(&tid, NULL, printNaturalNumbers, (void *)&n);

    // Wait for the thread to finish
    pthread_join(tid, NULL);

    return 0;
}
