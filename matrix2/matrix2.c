#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix_s {
    size_t R, C;
    int *index;
} Matrix;

Matrix *read_matrix() {
    Matrix *M = (Matrix*)malloc(sizeof(*M));

    scanf("%u %u", &M->R, &M->C);
    M->index = (int*)malloc(M->R * M->C * sizeof(*M->index));
    for (size_t i = 0; i < M->R; i++)
        for (size_t j = 0; j < M->C; j++)
            scanf("%d", &M->index[i * M->C + j]);
    return M;
}

Matrix *multiply_matrices(Matrix *A, Matrix *B) {
    Matrix *C = (Matrix*)malloc(sizeof(*C));

    if (A->C != B->R) {
        C->R = 0;
        C->C = 0;
        C->index = NULL;
        return C;
    }

    C->R = A->R;
    C->C = B->C;
    C->index = (int*)malloc(C->R * C->C * sizeof(*C->index));
    for (size_t i = 0; i < C->R; i++) {
        for (size_t j = 0; j < C->C; j++) {
            C->index[i * C->C + j] = 0;
            for (size_t k = 0; k < A->C; k++)
                C->index[i * C->C + j] += A->index[i * A->C + k] * B->index[k * B->C + j];
        }
    }
    return C;
}

void print_matrix(Matrix *M) {
    printf("%u %u\n", M->R, M->C);
    for (size_t i = 0; i < M->R; i++) {
        for (size_t j = 0; j < M->C; j++) {
            if (j)
                printf(" ");
            printf("%d", M->index[i * M->C + j]);
        }
        printf("\n");
    }
}

void delete_matrix(Matrix **M) {
    free((*M)->index);
    free(*M);
    *M = NULL;
}

int main() {
    Matrix *A, *B, *C;

    A = read_matrix();
    B = read_matrix();
    C = multiply_matrices(A, B);
    print_matrix(C);
    delete_matrix(&A);
    delete_matrix(&B);
    delete_matrix(&C);
    return 0;
}
