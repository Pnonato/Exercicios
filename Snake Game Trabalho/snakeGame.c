#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAX_RECORDS 5

typedef struct {
    int numeroJogador;
    char nome[50];
    int pontos;
} Recorde;

typedef struct Node {
    Recorde recorde;
    struct Node* proximo;
} Node;

Node* filaRecordes = NULL;

void enfileirarRecorde(char nome[], int pontos) {
    Node* novoRecorde = (Node*)malloc(sizeof(Node));
    static int contadorJogador = 1;  
    novoRecorde->recorde.numeroJogador = contadorJogador++;
    strcpy(novoRecorde->recorde.nome, nome);
    novoRecorde->recorde.pontos = pontos;
    novoRecorde->proximo = NULL;

    if (filaRecordes == NULL) {
        filaRecordes = novoRecorde;
    } else {
        Node* temp = filaRecordes;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoRecorde;
    }
}

void exibirRecordes() {
    printf("\nRecordes:\n");
    Node* temp = filaRecordes;
    while (temp != NULL) {
        printf("Nome: Jogador %d\tPontos: %d\n", temp->recorde.numeroJogador, temp->recorde.pontos);
        temp = temp->proximo;
    }
}

void atualizarRecordes(char nome[], int pontos) {
    enfileirarRecorde(nome, pontos);

    while (filaRecordes != NULL && filaRecordes->proximo != NULL &&
           filaRecordes->proximo->proximo != NULL) {
        Node* temp = filaRecordes;
        filaRecordes = filaRecordes->proximo;
        free(temp);
    }
}



int c[300][2], pontos = 1, cx = 2, cy = 2, comida[2], velo = 150;
char dir;
int gameover = 0;

void gotoxy(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
}

void desenha() {
    int i;
    for (i = 0; i < pontos; i++) {
        gotoxy(c[i][0], c[i][1]);
        printf("%c", 219);
    }
}

void atualiza() {
    int i;
    gotoxy(c[pontos][0], c[pontos][1]);
    printf(" ");
    for (i = pontos; i > 0; i--) {
        c[i][0] = c[i - 1][0];
        c[i][1] = c[i - 1][1];
    }
}

int analiza() {
    int i, retorno = 0;
    for (i = 1; i < pontos; i++) {
        if (cx == c[i][0] && cy == c[i][1]) {
            retorno = 1;
        }
    }

    return retorno;
}

void gerarComida() {
    gotoxy(comida[0], comida[1]);
    printf(" ");
    srand(time(NULL));
    comida[0] = (rand() % 48) + 1;
    comida[1] = (rand() % 18) + 1;
    gotoxy(comida[0], comida[1]);
    printf("%c", 4);
}

void reiniciarJogo() {
    pontos = 1;
    cx = 2;
    cy = 2;
    velo = 150;
    dir = 'd';
    gerarComida();
    gameover = 0;
}

int exibirMenu() {
    int escolha;
    system("cls");
    printf("1. Jogar\n");
    printf("2. Ver Recordes\n");
    printf("3. Sair\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

int main() {
    int i;
    char tecla;
    int escolha;

    do {
        escolha = exibirMenu();

        switch (escolha) {
            case 1:
                system("cls");
                reiniciarJogo();

                for (i = 0; i < 50; i++) {
                    gotoxy(i, 0);
                    printf("%c", 219);
                    Sleep(5);
                }

                for (i = 0; i < 20; i++) {
                    gotoxy(50, i);
                    printf("%c", 219);
                    Sleep(5);
                }

                for (i = 50; i >= 0; i--) {
                    gotoxy(i, 20);
                    printf("%c", 219);
                    Sleep(5);
                }

                for (i = 20; i >= 0; i--) {
                    gotoxy(0, i);
                    printf("%c", 219);
                    Sleep(5);
                }

                gerarComida();
                desenha();
                tecla = 'd';

                while (gameover == 0) {
                    gotoxy(52, 2);
                    printf("Use as teclas WASD para se mover");
                    gotoxy(52, 4);
                    printf("Pontos: %d\t", pontos);
                    gotoxy(52, 6);
                    printf("Velocidade: %.2f caracteres/s", 1000.0 / velo);
                    gotoxy(52, 8);
                    printf("Participantes: Pedro Nonato e Leo Villa");
                    c[0][0] = cx;
                    c[0][1] = cy;

                    if (kbhit()) {
                        tecla = getch();
                    }

                    if ((tecla == 'w' || tecla == 'W' || tecla == 72) && dir != 'S') {
                        dir = 'W';
                    }
                    if ((tecla == 'a' || tecla == 'A' || tecla == 75) && dir != 'D') {
                        dir = 'A';
                    }
                    if ((tecla == 's' || tecla == 'S' || tecla == 80) && dir != 'W') {
                        dir = 'S';
                    }
                    if ((tecla == 'd' || tecla == 'D' || tecla == 77) && dir != 'A') {
                        dir = 'D';
                    }

                    if (cx == comida[0] && cy == comida[1]) {
                        pontos++;
                        if (velo > 50) {
                            velo -= 10;
                        }
                        gerarComida();
                    }

                    gameover = analiza();
                    atualiza();
                    if (dir == 'W') {
                        cy--;
                    }
                    if (dir == 'A') {
                        cx--;
                    }
                    if (dir == 'S') {
                        cy++;
                    }
                    if (dir == 'D') {
                        cx++;
                    }
                    desenha();
                    gotoxy(50, 20);
                    Sleep(velo);

                    if (cx == 0 || cx == 50 || cy == 0 || cy == 20) {
                        gameover = 1;
                        atualizarRecordes("Nome do Jogador", pontos);
                        exibirRecordes();
                    }
                }

                system("cls");
                printf("Você perdeu! Fez %d pontos.\n", pontos);
                system("pause");
                break;
            case 2:
                exibirRecordes();
                system("pause");
                break;
            case 3:
                break;
            default:
                printf("Escolha inválida. Tente novamente.\n");
                system("pause");
                break;
        }

    } while (escolha != 3);

    return 0;
}
