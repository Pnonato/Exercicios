#include <stdio.h>

int funcao(int array[]) {
    int soma = 0;

    for (int i = 0; i < 4; i++) {
        soma += array[i];
    }

    return soma;
}

int main() {
    int array[4] = {4, 5, 34, 43};

    printf("Soma dos elementos do array: %d\n", funcao(array));

    return 0;
}
