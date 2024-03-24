#include "matrix.h"

void swapMinAndMaxRows(matrix m) {
    position minPos = getMinValuePos(m);
    position maxPos = getMaxValuePos(m);

    swapRows(&m, minPos.rowIndex, maxPos.rowIndex);
}

int getMax(int *a, int n) {
    int max = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

int getMin(int *a, int n) {
    int min = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

matrix mulMatrices(matrix m1, matrix m2) {
    matrix result = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return result;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (!isSquareMatrix(m)) {
        return;
    }

    if (!isSymmetricMatrix(m)) {
        return;
    }

    matrix squared = mulMatrices(*m, *m);

    freeMemMatrix(m);
    *m = squared;
}

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                return false;
            }
        }
    }
    return true;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long rowSums[m.nRows];

    for (int i = 0; i < m.nRows; ++i) {
        rowSums[i] = getSum(m.values[i], m.nCols);
    }

    if (isUnique(rowSums, m.nRows)) {
        transposeSquareMatrix(&m);
    }
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    if (!isSquareMatrix(&m1) || !isSquareMatrix(&m2)) {
        return false;
    }

    matrix product = mulMatrices(m1, m2);

    bool result = isEMatrix(&product);

    freeMemMatrix(&product);
    return result;
}

void outputArray(int *a, int n) {
    for(size_t i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long sum = 0;
    int nRows = m.nRows;
    int nCols = m.nCols;

    int pseudoDiagonalsCount = nRows + nCols - 2;
    int *maxElements = (int *)malloc(pseudoDiagonalsCount * sizeof(int));

    for (int i = 0; i < pseudoDiagonalsCount; ++i) {
        maxElements[i] = INT_MIN;
    }

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            int pseudoDiagonalIndex = i + (nCols - 1) - j;
            if (m.values[i][j] > maxElements[pseudoDiagonalIndex]) {
                maxElements[pseudoDiagonalIndex] = m.values[i][j];
            }
        }
    }

    for (int i = 0; i < pseudoDiagonalsCount; ++i) {
        sum += maxElements[i];
    }

    free(maxElements);
    return sum;
}



void task1() {
    int value1[] = {3, 12, 4, 2, 8, 12, 6, 4, 0};
    int value2[] = {10, 2, 5, 8, 1, 15, 3, 4, 7, 6, 12, 9, 11, 4, 14, 13};
    int value3[] = {3,2,1,0};
    matrix m1 = createMatrixFromArray(value1, 3, 3);
    matrix m2 = createMatrixFromArray(value2, 4, 4);
    matrix m3 = createMatrixFromArray(value3, 2, 2);

    swapMinAndMaxRows(m1);
    swapMinAndMaxRows(m2);
    swapMinAndMaxRows(m3);

    assert(m1.values[0][0] == 6 && m1.values[1][1] == 8 && m1.values[2][2] == 4);
    assert(m2.values[0][0] == 10 && m2.values[1][1] == 15 && m2.values[2][2] == 12 && m2.values[3][0] == 11);
    assert(m3.values[0][0] == 1 && m3.values[0][1] == 0 && m3.values[1][1] == 2);
}

void task2() {
    int values1[] = {7, 1, 2, 1, 8, 1, 3, 2, 3};
    int values2[] = {2, 5, 2, 8, 4, 1, 4, 8, 3, 8, 3, 6, 1, 2, 7, 8};

    matrix m1 = createMatrixFromArray(values1, 3, 3);
    matrix m2 = createMatrixFromArray(values2, 4, 4);

    insertionSortRowsMatrixByRowCriteria(&m1, getMax);
    insertionSortRowsMatrixByRowCriteria(&m2, getMax);

    assert(m1.values[0][0] == 3 && m1.values[0][1] == 2 && m1.values[1][1] == 1 && m1.values[2][2] == 1);
    assert(m2.values[0][0] == 2 && m2.values[0][1] == 5 && m2.values[1][1] == 1 && m2.values[2][0] == 3 && m2.values[3][1] == 2);
}

void task3() {
    int values1[] = {3, 5, 2, 4, 3, 3, 2, 5 ,1, 8, 2, 7, 6, 1, 4, 4, 8, 3};
    int values2[] = {2, 5, 12, 8, 1, 4, 1, 4, 8, 6, 3, 1, 3, 6, 11, 1, 2, 7, 8, 15};

    matrix m1 = createMatrixFromArray(values1, 3, 6);
    matrix m2 = createMatrixFromArray(values2, 4, 5);

    selectionSortColsMatrixByColCriteria(m1, getMin);
    selectionSortColsMatrixByColCriteria(m2, getMin);

    assert(m1.values[0][0] == 5 && m1.values[1][1] == 1 && m1.values[1][4] == 7 && m1.values[2][2] == 6);
    assert(m2.values[0][0] == 2 && m2.values[1][3] == 4 && m2.values[2][4] == 6 && m2.values[3][3] == 7);
}

void task4() {
    int values1[] = {1,2,3,2,4,5,3,5,6};
    int values2[] = {1,2,3,4,5,6,7,8,9};
    matrix m1 = createMatrixFromArray(values1, 3, 3);
    matrix m2 = createMatrixFromArray(values2, 3, 3);

    getSquareOfMatrixIfSymmetric(&m1);
    getSquareOfMatrixIfSymmetric(&m2);

    assert(m1.values[0][0] == 14 && m1.values[1][0] == 25 && m1.values[2][1] == 56);
    assert(m2.values[0][0] == 1 && m2.values[1][0] == 4 && m2.values[2][1] == 8);
}

void task5() {
    int values1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int values2[] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    matrix m1 = createMatrixFromArray(values1, 3, 3);
    matrix m2 = createMatrixFromArray(values2, 3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(m1);
    transposeIfMatrixHasNotEqualSumOfRows(m2);

    assert(m1.values[0][0] == 1 && m1.values[0][1] == 4 && m1.values[2][1] == 6);
    assert(m2.values[0][0] == 1 && m2.values[0][1] == 2 && m2.values[2][1] == 2);
}

void task6() {
    int values1[] = {1, 0, 0, 1};
    matrix m1 = createMatrixFromArray(values1, 2, 2);
    int values2[] = {1, 0, 0, 1};
    matrix m2 = createMatrixFromArray(values2, 2, 2);
    int values3[] = {1, 2, 3, 4};
    matrix m3 = createMatrixFromArray(values3, 2, 2);
    int values4[] = {1, 2, 3, 4, 5, 6};
    matrix m4 = createMatrixFromArray(values4, 3, 2);

    assert(isMutuallyInverseMatrices(m1, m2));
    assert(!isMutuallyInverseMatrices(m3, m4));

}

void task7() {
    int values1[] = {3,2,5,4,1,3,6,3,3,2,1,2};
    int values2[] = {-3, -2, -5, -4, -1, -3, -6, -3};
    matrix m1 = createMatrixFromArray(values1, 3, 4);
    matrix m2 = createMatrixFromArray(values2, 4, 2);

    assert(findSumOfMaxesOfPseudoDiagonal(m1) == 20);
    assert(findSumOfMaxesOfPseudoDiagonal(m2) == -9);
}


int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    return 0;
}