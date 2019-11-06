#include <stdio.h>

#define MAXN 300

typedef struct Matrix_s {
    size_t R, C;
    int index[MAXN][MAXN];
} Matrix;

Matrix read_matrix() {
    Matrix M;

    scanf("%u %u", &M.R, &M.C);
    for (size_t i = 0; i < M.R; i++)
        for (size_t j = 0; j < M.C; j++)
            scanf("%d", &M.index[i][j]);
    return M;
}

Matrix multiply(Matrix A, Matrix B) {
    Matrix C;

    if (A.C != B.R) {
        C.R = 0;
        C.C = 0;
        return C;
    }
    C.R = A.R;
    C.C = B.C;
    for (size_t i = 0; i < A.R; i++) {
        for (size_t j = 0; j < B.C; j++) {
            C.index[i][j] = 0;
            for (size_t k = 0; k < A.C; k++)
                C.index[i][j] += A.index[i][k] * B.index[k][j];
        }
    }
    return C;
}

void print_matrix(Matrix A) {
    printf("%u %u\n", A.R, A.C);
    for (size_t i = 0; i < A.R; i++) {
        for (size_t j = 0; j < A.C; j++) {
            if (j > 0)
                printf(" ");
            printf("%d", A.index[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix A, B, C;

    A = read_matrix();
    B = read_matrix();
    C = multiply(A, B);
    print_matrix(C);
    return 0;
}
