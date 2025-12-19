#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5

// STRUCT DA PEÇA
typedef struct {
    char tipo;
    int id;
} Peca;

// STRUCT DA FILA
typedef struct {
    Peca fila[TAMANHO];
    int inicio;
    int fim;
    int total;
} Fila;

// PROTÓTIPOS
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca(int id);
void inicializarFila(Fila *f, int *contadorId);
void enqueue(Fila *f, int *contadorId);
void dequeue(Fila *f);
void mostrarFila(Fila *f);

// FUNÇÃO PRINCIPAL
int main() {
    srand(time(NULL));

    Fila fila;
    int contadorId = 0;
    int opcao;

    inicializarFila(&fila, &contadorId);

    do {
        mostrarFila(&fila);

        printf("\n1 - Jogar peça\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            dequeue(&fila);
            enqueue(&fila, &contadorId);
        }

    } while (opcao != 0);

    return 0;
}

// FUNÇÕES

int filaCheia(Fila *f) {
    return f->total == TAMANHO;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

void inicializarFila(Fila *f, int *contadorId) {
    f->inicio = 0;
    f->fim = -1;
    f->total = 0;

    for (int i = 0; i < TAMANHO; i++) {
        f->fim = (f->fim + 1) % TAMANHO;
        f->fila[f->fim] = gerarPeca(*contadorId);
        (*contadorId)++;
        f->total++;
    }
}

void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n⚠️ Fila vazia!\n");
        return;
    }

    printf("\n🎮 Jogando peça [%c]\n", f->fila[f->inicio].tipo);

    f->inicio = (f->inicio + 1) % TAMANHO;
    f->total--;
}

void enqueue(Fila *f, int *contadorId) {
    if (filaCheia(f)) {
        return;
    }

    f->fim = (f->fim + 1) % TAMANHO;
    f->fila[f->fim] = gerarPeca(*contadorId);
    (*contadorId)++;
    f->total++;
}

void mostrarFila(Fila *f) {
    printf("\nFila de peças:\n");

    int index = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->fila[index].tipo, i);
        index = (index + 1) % TAMANHO;
    }
    printf("\n");
}
