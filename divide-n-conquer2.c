#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

/* Function to display a matrix */
void displayMatrix(int *_Matrix, int _Size) {
    for (int i = 0; i < _Size; i++) {
        for (int j = 0; j < _Size; j++) {
            printf("%2d ", *(_Matrix + i * _Size + j));
        }
        printf("\n");
    }
    printf("\n");
}

/* Function to divide a matrix into four sub-matrices */
int divMatrix(int *_Matrix, int _Size, int **_pSubMatrix, int _subSize) {
    int n = 0;
    int subOffset = 0;
    int indexSubMatrix = 0;
    int indexMatrix = 0;

    *_pSubMatrix = (int *)malloc(4 * (_Size / 2 * _Size / 2) * sizeof(int));

    for (int i = 0; i < _Size; i++) {
        for (int j = 0; j < _Size; j++) {
            if (i < _Size / 2 && j < _Size / 2) {
                n = 0;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + i * _Size / 2 + j;
                *(*_pSubMatrix + indexSubMatrix) = _Matrix[indexMatrix];
            } else if (i < _Size / 2 && j >= _Size / 2) {
                n = 1;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + i * _Size / 2 + (j - _Size / 2);
                *(*_pSubMatrix + indexSubMatrix) = _Matrix[indexMatrix];
            } else if (i >= _Size / 2 && j < _Size / 2) {
                n = 2;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + (i - _Size / 2) * _Size / 2 + j;
                *(*_pSubMatrix + indexSubMatrix) = _Matrix[indexMatrix];
            } else {
                n = 3;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + (i - _Size / 2) * _Size / 2 + (j - _Size / 2);
                *(*_pSubMatrix + indexSubMatrix) = _Matrix[indexMatrix];
            }
        }
    }

    return _Size / 2 * _Size / 2;
}

/* Function to multiply matrices */
void multiplyMatrix(int *A, int *B, int *C, int _Size) {
    for (int i = 0; i < _Size; i++) {
        for (int j = 0; j < _Size; j++) {
            int cij = *(C + i * _Size + j);
            int eSum = 0;

            for (int k = 0; k < _Size; k++) {
                int aik = *(A + i * _Size + k);
                int bkj = *(B + k * _Size + j);
                eSum += aik * bkj;
            }

            cij += eSum;
            *(C + i * _Size + j) = cij;
            printf("%2d ", *(C + i * _Size + j));
        }
        printf("\n");
    }
    printf("\n");
}

/* Function to merge sub-matrices into a single matrix */
int mergeMatrix(int **_SubMatrix, int _subSize, int **_Matrix) {
    int n = 0;
    int subOffset = 0;
    int _Size = 2 * _subSize;
    int indexSubMatrix = 0;
    int indexMatrix = 0;

    *_Matrix = (int *)malloc((_Size * _Size) * sizeof(int));

    for (int i = 0; i < _Size; i++) {
        for (int j = 0; j < _Size; j++) {
            if (i < _Size / 2 && j < _Size / 2) {
                n = 0;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + i * _Size / 2 + j;
                *(*_Matrix + indexMatrix) = *(*_SubMatrix + indexSubMatrix);
            } else if (i < _Size / 2 && j >= _Size / 2) {
                n = 1;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + i * _Size / 2 + (j - _Size / 2);
                *(*_Matrix + indexMatrix) = *(*_SubMatrix + indexSubMatrix);
            } else if (i >= _Size / 2 && j < _Size / 2) {
                n = 2;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + (i - _Size / 2) * _Size / 2 + j;
                *(*_Matrix + indexMatrix) = *(*_SubMatrix + indexSubMatrix);
            } else {
                n = 3;
                subOffset = n * (_Size / 2 * _Size / 2);
                indexMatrix = i * _Size + j;
                indexSubMatrix = subOffset + (i - _Size / 2) * _Size / 2 + (j - _Size / 2);
                *(*_Matrix + indexMatrix) = *(*_SubMatrix + indexSubMatrix);
            }
        }
    }

    return _Size;
}

/* Function to add matrices element-wise */
void addMatrix(int *A, int *B, int *C, int _Size) {
    for (int i = 0; i < _Size; i++) {
        for (int j = 0; j < _Size; j++) {
            int aij = *(A + i * _Size + j);
            int bij = *(B + i * _Size + j);
            int cij = *(C + i * _Size + j);

            cij = cij + aij + bij;
            *(C + i * _Size + j) = cij;
            printf("%2d ", *(C + i * _Size + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    /* Define three matrices with 4*4 elements */
    int mA[N][N] = {
        {1, 3, 0, 7},
        {2, 5, 2, 1},
        {4, 2, 3, 4},
        {3, 1, 1, 5}
    };
    int mB[N][N] = {
        {5, 1, 1, 2},
        {1, 0, 6, 3},
        {2, 9, 1, 2},
        {7, 2, 5, 2}
    };
    int mC[N][N] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    printf("Original Matrix A:\n");
    displayMatrix(&mA[0][0], N);
    printf("Original Matrix B:\n");
    displayMatrix(&mB[0][0], N);
    printf("Original Matrix C:\n");
    displayMatrix(&mC[0][0], N);

    /* Divide big matrix into four sub-matrices A */
    int *SubMtrxA, *pSubMtrxA[4];
    int *BigMtrxA;
    int subsize = divMatrix(&mA[0][0], N, &SubMtrxA, N / 2);
    printf("\nSubMatrices[A], (A11, A12, A21, A22) = %2d \n", subsize);

    for (int i = 0; i < 4; i++) {
        pSubMtrxA[i] = SubMtrxA + i * (N / 2 * N / 2);
        displayMatrix(pSubMtrxA[i], N / 2);
    }

    /* Divide big matrix into four sub-matrices B */
    int *SubMtrxB, *pSubMtrxB[4];
    int *BigMtrxB;
    int subsizeB = divMatrix(&mB[0][0], N, &SubMtrxB, N / 2);
    printf("\nSubMatrices[B], (B11, B12, B21, B22) = %2d \n", subsizeB);

    for (int i = 0; i < 4; i++) {
        pSubMtrxB[i] = SubMtrxB + i * (N / 2 * N / 2);
        displayMatrix(pSubMtrxB[i], N / 2);
    }

    /* Multiply sub-Matrices and Add together sub-Matrices, e.g., C11 = A11 * B11 + A12 * B21 */
    int *A11, *B11, *A12, *B21;
    A11 = pSubMtrxA[0];
    B11 = pSubMtrxB[0];
    A12 = pSubMtrxA[1];
    B21 = pSubMtrxB[2];

    printf("\nMultiply Matrices of A11 * B11 + A12 * B21.\n");
    int submC11[2][2];
    int submA11B11[2][2];
    int submA12B21[2][2];
    memset(submC11, 0, sizeof(submC11));
    memset(submA11B11, 0, sizeof(submA11B11));
    memset(submA12B21, 0, sizeof(submA12B21));

    /* Multiply sub-Matrices */
    multiplyMatrix(A11, B11, submA11B11[0], N / 2);
    multiplyMatrix(A12, B21, submA12B21[0], N / 2);

    /* Add together sub-Matrices */
    addMatrix(submA11B11[0], submA12B21[0], submC11[0], N / 2);

    /* Compare sub-summation with big-summation with the algorithm of divide-and-conquer */
    printf("\nMultiply Matrices of C = A * B.\n");
    int submC[2][2];
    memset(submC, 0, sizeof(submC));
    multiplyMatrix(&mA[0][0], &mB[0][0], &mC[0][0], N);

    /* Merge sub-subsummation matrix */
    int bigsize = mergeMatrix(&SubMtrxA, N / 2, &BigMtrxA);
    printf("\nThe Merged Sub-Matrices = %2d \n", bigsize);
    displayMatrix(BigMtrxA, bigsize);

    /* Compare sub-summation with big-multiplication */
    printf("\nAfter Multiplying Matrix:\n");
    displayMatrix(&mC[0][0], N);

    /* Release allocated memories */
    free(BigMtrxA);
    free(SubMtrxA);
    free(BigMtrxB);
    free(SubMtrxB);

    return 0;
}
