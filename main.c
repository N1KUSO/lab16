#include "matrix.h"

void swapMinAndMaxRows(matrix m) {
    position minPos = getMinValuePos(m);
    position maxPos = getMaxValuePos(m);

    swapRows(&m, minPos.rowIndex, maxPos.rowIndex);
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

    printf("Task 1 done.\n");
}


int main() {
    task1();
    return 0;
}