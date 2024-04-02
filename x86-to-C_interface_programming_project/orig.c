#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1073741824// Define vector size

// Function to perform 1-D stencil operation
void stencil(float *X, float *Y, int n) {
    if(n < 7 )
    {
        printf("Not enough vector size to perform stencil");
        return;
    }


    for (int i = 0; i < n - 6; ++i) {
        for(int j = i + 2; j >= i; j--)
            Y[i] += X[j];
        for(int k = i + 3; k < i + 7; k++)
            Y[i] += X[k];
    }
}

int main() {
    // Allocate memory for vectors X and Y
    float *X = (float *)malloc(N * sizeof(float));
    float *Y = (float *)malloc((N - 6) * sizeof(float));

    // Initialize vector X with random values
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        //X[i] = rand() % 100; // Random values between 0 and 99
        X[i] = i + 1; // Random values between 0 and 99
    }

    clock_t start_time = clock(); // Start clock

    // Call the stencil function
    stencil(X, Y, N);
    clock_t end_time = clock(); // End clock

    // printf("Resulting vector X:\n");
    // for (int i = 0; i < N; ++i) {
    //     printf("%.2f ", X[i]);
    // }
    printf("\n\n");

    printf("Resulting vector Y:\n");
    for (int i = N - 16; i < N - 6; ++i) {
        printf("%.2f ", Y[i]);
    }
    printf("\n");

    double total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", total_time);

    // Free allocated memory
    free(X);
    free(Y);

    return 0;
}