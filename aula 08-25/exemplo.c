#include <stdio.h>


int main(){
    int *p;
    int no1 = 350;
    int no2 = 1080;
    
    printf("Endereco de p: %p \n", &p);

    printf("Endereco de no1: %p\n", &no1);

    printf("Endereco de no2: %p\n", &no2);

    p = &no1;
    printf("valor de p: %p \n");
    printf("valor *p: %d\n");

    *p = 256;

    printf("valor de no2: %d\n", no2);

    return 0;



}