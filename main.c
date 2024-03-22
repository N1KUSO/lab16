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

int main() {
    task1();
    task2();
    return 0;
}