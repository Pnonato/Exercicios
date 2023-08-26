#include <stdio.h>

int main(){


    int *p;
    int numb1 = 12;

    printf("Valor de numero 1: %d\n", numb1);

    p = &numb1;
    *p = 23;

    printf("Valor de numero 1 mudado com o ponteiro: %d\n", *p);


}