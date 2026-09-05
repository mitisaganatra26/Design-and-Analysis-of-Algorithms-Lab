#include <stdio.h>

int main() {
    int r1, c1, r2, c2;

    // Read dimensions for Matrix A
    if (scanf("%d %d", &r1, &c1) != 2) return 0;

    // Read elements of Matrix A
    int A[r1][c1];
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Read dimensions for Matrix B
    if (scanf("%d %d", &r2, &c2) != 2) return 0;

    // Check if matrix multiplication is possible
    if (c1 != r2) {
        printf("Invalid input\n");
        return 0;
    }

    // Read elements of Matrix B only if multiplication is possible
    int B[r2][c2];
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Compute matrix product C = A x B
    int C[r1][c2];
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Display the product matrix
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
