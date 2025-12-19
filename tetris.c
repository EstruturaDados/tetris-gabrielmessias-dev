#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// VARIAVEIS GLOBAIS TAMANHOS FIXOS DA FILA E DA PILHA PRO TETRIS
#define TAM_FILA 5
#define TAM_PILHA 3

// STRUCT DA PEÇA
typedef struct {
    char tipo;
    int id;
} Peca;

// STRUCT DA FILA
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// ADD STRUCT DA PILHA
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} Pilha;

// PROTOTIPOS
Peca gerarPeca(int id);

// FILA
void inicializarFila(Fila *f, int *contadorId);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);

// PILHA
void inicializarPilha(Pilha *p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void push(Pilha *p, Peca peca);
Peca pop(Pilha *p);

// EXIBIR
void mostrarEstado(Fila *f, Pilha *p);

// FUNÇÃO PRINCIPAL
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    int contadorId = 0;
    int opcao;

    inicializarFila(&fila, &contadorId);
    inicializarPilha(&pilha);

    do {
        mostrarEstado(&fila, &pilha);

        printf("\n1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            dequeue(&fila);
            enqueue(&fila, gerarPeca(contadorId++));
        }
        else if (opcao == 2) {
            if (!pilhaCheia(&pilha)) {
                push(&pilha, dequeue(&fila));
                enqueue(&fila, gerarPeca(contadorId++));
            } else {
                printf("\n Pilha cheia! Não e possivel reservar.\n");
            }
        }
        else if (opcao == 3) {
            if (!pilhaVazia(&pilha)) {
                pop(&pilha);
                enqueue(&fila, gerarPeca(contadorId++));
            } else {
                printf("\n Pilha vazia!\n");
            }
        }

    } while (opcao != 0);

    return 0;
}

// IMPLEMENTAÇÕES

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// FILA

void inicializarFila(Fila *f, int *contadorId) {
    f->inicio = 0;
    f->fim = -1;
    f->total = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(f, gerarPeca((*contadorId)++));
    }
}

void enqueue(Fila *f, Peca p) {
    f->fim = (f->fim + 1) % TAM_FILA;
    f->fila[f->fim] = p;
    f->total++;
}

Peca dequeue(Fila *f) {
    Peca removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;
    return removida;
}

// PILHA

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca peca) {
    p->topo++;
    p->pilha[p->topo] = peca;
}

Peca pop(Pilha *p) {
    return p->pilha[p->topo--];
}

// EXIBIR

void mostrarEstado(Fila *f, Pilha *p) {
    printf("\nEstado atual:\n");

    printf("Fila de peças: ");
    int index = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->fila[index].tipo, f->fila[index].id);
        index = (index + 1) % TAM_FILA;
    }

    printf("\nPilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("vazia");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pilha[i].tipo, p->pilha[i].id);
        }
    }
    printf("\n");
}
