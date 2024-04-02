#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h> // Required for SIMD intrinsics
#include <time.h>      // Required for clock functionality

void stencil_simd(float *X, float *Y, int n) {
    if (n < 7) {
        printf("Not enough vector size to perform stencil\n");
        return;
    }

    for (int i = 3; i < n - 3; ++i) {
        // Initialize sum to zero
        float sum = 0.0;
        // Add values from X to sum
        for (int j = -3; j <= 3; ++j) {
            sum += X[i + j];
        }
        // Store sum in Y
        Y[i - 3] = sum;
    }
}

int main() {
    long long n = 8;
    float *X = malloc(n * sizeof(float));
    float *Y = malloc((n - 6) * sizeof(float));

    // Initialize array X
    for (int i = 0; i < n; ++i) {
        X[i] = (float)(i + 1); // Initialize each element individually
    }

    clock_t start_time = clock(); // Start clock

    stencil_simd(X, Y, n);

    clock_t end_time = clock(); // End clock

     printf("Resulting vector X:\n");
    for (int i = 0; i < n; ++i) {
        printf("%.2f ", X[i]);
    }
    printf("\n\n");

    printf("Resulting vector Y:\n");
    for (int i = 0; i < n - 6; ++i) {
        printf("%.2f ", Y[i]);
    }
    printf("\n");
    
    // Calculate and print execution time
    double total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", total_time);
    free(X);
    free(Y);
}
