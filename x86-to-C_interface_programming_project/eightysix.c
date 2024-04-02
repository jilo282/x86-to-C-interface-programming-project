#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h> // Required for SIMD intrinsics
#include <time.h>      // Required for clock functionality

void stencil_simd(float *X, float *Y, int n) {
    if (n < 7) {
        printf("Not enough vector size to perform stencil\n");
        return;
    }

    // Iterate over the vector using SIMD
    for (int i = 3; i < n - 3; i += 8) {
        // Load 8 elements from X into SIMD register
        __m256 sum_vec = _mm256_setzero_ps();

        // Perform the stencil operation using SIMD
        for (int j = -3; j <= 3; ++j) {
            __m256 x_vec = _mm256_loadu_ps(&X[i + j]);
            sum_vec = _mm256_add_ps(sum_vec, x_vec);
        }

        // Store the result back to Y
        _mm256_storeu_ps(&Y[i - 3], sum_vec);
    }
}
int main() {
    long long n = 1073741824;
    float *X = malloc(n * sizeof(float));
    float *Y = malloc((n - 6) * sizeof(float));

    // Initialize array X
    for (int i = 0; i < n; ++i) {
        X[i] = (float)(i + 1); // Initialize each element individually
    }

    clock_t start_time = clock(); // Start clock

    stencil_simd(X, Y, n);

    clock_t end_time = clock(); // End clock

    //  printf("Resulting vector X:\n");
    // for (int i = 0; i < n; ++i) {
    //     printf("%.2f ", X[i]);
    // }
    printf("\n\n");

    printf("Resulting vector Y:\n");
    for (int i = n - 16; i < n - 6; ++i) {
        printf("%.2f ", Y[i]);
    }
    printf("\n");
    
    // Calculate and print execution time
    double total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", total_time);
    free(X);
    free(Y);
}
