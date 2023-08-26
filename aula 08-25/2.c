#include <stdio.h>

void findMaxValueAndPosition(const int *array, int size, int *maxValue, int *maxPosition) {
    if (size <= 0) {
        *maxValue = 0;
        *maxPosition = -1;
        return;
    }

    *maxValue = array[0];
    *maxPosition = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] > *maxValue) {
            *maxValue = array[i];
            *maxPosition = i;
        }
    }
}

int main() {
    int array[] = {12, 45, 7, 89, 23, 67, 34};
    int size = sizeof(array) / sizeof(array[0]);

    int maxValue, maxPosition;
    findMaxValueAndPosition(array, size, &maxValue, &maxPosition);

    printf("Maior valor: %d\n", maxValue);
    printf("Posição do maior valor: %d\n", maxPosition);

    return 0;
}
