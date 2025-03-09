#include <stdio.h>

#define MAX 10

void read_matrix(int mat[MAX][MAX], int rows, int cols) {
    printf("Enter elements of %d x %d matrix:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

// Function to display a matrix
void display_matrix(int mat[MAX][MAX], int rows, int cols) {
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}


void add_matrices(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


void multiply_matrices(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void transpose_matrix(int A[MAX][MAX], int T[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            T[j][i] = A[i][j];
        }
    }
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX], T[MAX][MAX];
    int rows, cols, choice;

    do {
        printf("\nMenu:\n");
        printf("1. Read Matrix\n");
        printf("2. Display Matrix\n");
        printf("3. Add Two Matrices\n");
        printf("4. Multiply Two Matrices\n");
        printf("5. Find Transpose of Matrix\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of rows and columns: ");
                scanf("%d %d", &rows, &cols);
                read_matrix(A, rows, cols);
                break;
            
            case 2:
                display_matrix(A, rows, cols);
                break;

            case 3:
                printf("Enter elements of second matrix:\n");
                read_matrix(B, rows, cols);
                add_matrices(A, B, C, rows, cols);
                printf("Sum of matrices:\n");
                display_matrix(C, rows, cols);
                break;

            case 4:
                {
                    int r2, c2;
                    printf("Enter number of rows and columns for second matrix: ");
                    scanf("%d %d", &r2, &c2);
                    
                    if (cols != r2) {
                        printf("Matrix multiplication not possible.\n");
                        break;
                    }
                    
                    printf("Enter elements of second matrix:\n");
                    read_matrix(B, r2, c2);
                    multiply_matrices(A, B, C, rows, cols, c2);
                    printf("Product of matrices:\n");
                    display_matrix(C, rows, c2);
                }
                break;

            case 5:
                transpose_matrix(A, T, rows, cols);
                printf("Transpose of matrix:\n");
                display_matrix(T, cols, rows);
                break;

            case 6:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
