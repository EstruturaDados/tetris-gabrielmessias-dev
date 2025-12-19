#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TAMANHOS FIXOS
#define TAM_FILA 5
#define TAM_PILHA 3

// STRUCT DA PEÇA
typedef struct {
    char tipo;
    int id;
} Peca;


// STRUCT DA FILA CIRCULAR
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int total;
} Fila;


// STRUCT DA PILHA
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} Pilha;


// PROTÓTIPOS


// GERAÇÃO
Peca gerarPeca(int id);

// FILA
void inicializarFila(Fila *f, int *contadorId);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);

// PILHA
void inicializarPilha(Pilha *p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void push(Pilha *p, Peca peca);
Peca pop(Pilha *p);

// TROCAS
void trocarAtual(Fila *f, Pilha *p);
void trocaMultipla(Fila *f, Pilha *p);

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

        printf("\nOpcoees:\n");
        printf("1 - Jogar peca da fila\n");
        printf("2 - Reservar peca (fila -> pilha)\n");
        printf("3 - Usar peca reservada\n");
        printf("4 - Trocar peca atual (fila <-> pilha)\n");
        printf("5 - Troca multipla (3 da fila <-> 3 da pilha)\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: // Jogar peça
                if (!filaVazia(&fila)) {
                    dequeue(&fila);
                    enqueue(&fila, gerarPeca(contadorId++));
                }
                break;

            case 2: // Reservar peça
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    push(&pilha, dequeue(&fila));
                    enqueue(&fila, gerarPeca(contadorId++));
                } else {
                    printf("\nNao foi possivel reservar.\n");
                }
                break;

            case 3: // Usar peça reservada
                if (!pilhaVazia(&pilha)) {
                    pop(&pilha); // peça some (uso no jogo)
                } else {
                    printf("\nPilha vazia.\n");
                }
                break;

            case 4: // Troca simples
                trocarAtual(&fila, &pilha);
                break;

            case 5: // Troca múltipla
                trocaMultipla(&fila, &pilha);
                break;
        }

    } while (opcao != 0);

    return 0;
}


// IMPLEMENTAÇÕES

// GERA PEÇA
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
    if (filaCheia(f)) return;

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

int filaCheia(Fila *f) {
    return f->total == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->total == 0;
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
    if (!pilhaCheia(p)) {
        p->pilha[++p->topo] = peca;
    }
}

Peca pop(Pilha *p) {
    return p->pilha[p->topo--];
}

// TROCA SIMPLES
void trocarAtual(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("\nTroca nao possivel.\n");
        return;
    }

    int idx = f->inicio;
    Peca temp = f->fila[idx];

    f->fila[idx] = pop(p);
    push(p, temp);
}

// TROCA MULTIPLA
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo + 1 < 3) {
        printf("\nTroca multipla nao possivel.\n");
        return;
    }

    Peca tempFila[3];
    Peca tempPilha[3];

    // Retira 3 da fila
    for (int i = 0; i < 3; i++) {
        tempFila[i] = dequeue(f);
    }

    // Retira 3 da pilha
    for (int i = 0; i < 3; i++) {
        tempPilha[i] = pop(p);
    }

    // Coloca pilha na frente da fila (ordem correta)
    for (int i = 2; i >= 0; i--) {
        f->inicio = (f->inicio - 1 + TAM_FILA) % TAM_FILA;
        f->fila[f->inicio] = tempPilha[i];
        f->total++;
    }

    // Coloca fila na pilha
    for (int i = 0; i < 3; i++) {
        push(p, tempFila[i]);
    }
}

// EXIBIR
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\nEstado atual:\n");

    printf("Fila de pecas: ");
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->fila[idx].tipo, f->fila[idx].id);
        idx = (idx + 1) % TAM_FILA;
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
