#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// ————————————————————————————————————————————————
// Tetris Stack (nível Novato): fila circular de peças futuras
// ————————————————————————————————————————————————

// Tipos de peça possíveis
static const char TIPOS[] = {'I', 'O', 'T', 'L'};

// Representa uma peça do jogo
typedef struct {
    char nome;  // 'I', 'O', 'T' ou 'L'
    int id;     // identificador único, crescente
} Peca;

// Fila circular de peças
typedef struct {
    Peca *dados;    // array de peças
    int capacidade; // tamanho máximo
    int frente;     // índice do primeiro elemento
    int tamanho;    // quantos elementos estão na fila
} FilaPecas;

// ————————————————————————————————————————————————
// Helpers da fila
// ————————————————————————————————————————————————

static void inicializarFila(FilaPecas *fila, int capacidade) {
    fila->dados = (Peca*) malloc(sizeof(Peca) * capacidade);
    fila->capacidade = capacidade;
    fila->frente = 0;
    fila->tamanho = 0;
}

static void liberarFila(FilaPecas *fila) {
    free(fila->dados);
    fila->dados = NULL;
    fila->capacidade = 0;
    fila->frente = 0;
    fila->tamanho = 0;
}

static bool filaVazia(const FilaPecas *fila) {
    return fila->tamanho == 0;
}

static bool filaCheia(const FilaPecas *fila) {
    return fila->tamanho == fila->capacidade;
}

static int indiceDaPosicao(const FilaPecas *fila, int pos) {
    // pos é relativo ao início lógico da fila
    return (fila->frente + pos) % fila->capacidade;
}

// ————————————————————————————————————————————————
// Geração de peças
// ————————————————————————————————————————————————

static Peca gerarPeca(void) {
    static int proximoId = 0; // garante id único e crescente
    Peca p;
    p.nome = TIPOS[rand() % (int)(sizeof(TIPOS) / sizeof(TIPOS[0]))];
    p.id = proximoId++;
    return p;
}

// ————————————————————————————————————————————————
// Operações da fila
// ————————————————————————————————————————————————

static bool enfileirar(FilaPecas *fila, Peca p) {
    if (filaCheia(fila)) return false;
    int idx = indiceDaPosicao(fila, fila->tamanho);
    fila->dados[idx] = p;
    fila->tamanho++;
    return true;
}

static bool desenfileirar(FilaPecas *fila, Peca *removida) {
    if (filaVazia(fila)) return false;
    if (removida) *removida = fila->dados[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    return true;
}

// ————————————————————————————————————————————————
// Visualização
// ————————————————————————————————————————————————

static void imprimirEstado(const FilaPecas *fila) {
    printf("\nConfira a seguir seu estado:\n\n");
    printf("Fila de peças\n");

    if (filaVazia(fila)) {
        printf("<vazia>\n");
    } else {
        for (int i = 0; i < fila->tamanho; i++) {
            int idx = indiceDaPosicao(fila, i);
            const Peca *p = &fila->dados[idx];
            printf("[%c %d] ", p->nome, p->id);
        }
        printf("\n");
    }

    printf("Tabela: Visualização da fila de peças.\n");
    printf("Curadoria de TI.\n\n");

    printf("Opções de ação:\n\n");
    printf("Código\tAção\n");
    printf("1\tJogar peça (dequeue)\n");
    printf("2\tInserir nova peça (enqueue)\n");
    printf("0\tSair\n");
    printf("Tabela: Comandos disponíveis para manipular a fila de peças.\n");
    printf("Curadoria de TI.\n\n");
}

// leitura segura de opção inteira (linha inteira -> parse)
static int lerOpcao(void) {
    char buf[64];
    if (!fgets(buf, sizeof(buf), stdin)) return -1;
    // tira \n
    char *p = strchr(buf, '\n');
    if (p) *p = '\0';

    // tenta converter
    char *end = NULL;
    long v = strtol(buf, &end, 10);
    if (end == buf) return -1; // nada lido
    return (int)v;
}

int main(void) {
    // aleatoriedade básica pra variar os tipos gerados
    srand((unsigned) time(NULL));

    FilaPecas fila;
    const int CAPACIDADE = 5; // tamanho fixo, como pedido
    inicializarFila(&fila, CAPACIDADE);

    // começo com a fila cheia, do jeitinho do enunciado
    for (int i = 0; i < CAPACIDADE; i++) {
        (void) enfileirar(&fila, gerarPeca());
    }

    // loop do menu enxuto
    while (1) {
        imprimirEstado(&fila);
        printf("Sua escolha: ");
        int opc = lerOpcao();
        printf("\n");

        if (opc == 0) {
            printf("Até mais!\n");
            break;
        } else if (opc == 1) {
            Peca jogada;
            if (desenfileirar(&fila, &jogada)) {
                printf("Você jogou: [%c %d]\n", jogada.nome, jogada.id);
            } else {
                printf("Não rola: a fila já está vazia.\n");
            }
        } else if (opc == 2) {
            if (filaCheia(&fila)) {
                printf("Não cabe: a fila já está cheia.\n");
            } else {
                Peca nova = gerarPeca();
                enfileirar(&fila, nova);
                printf("Inserida nova peça: [%c %d]\n", nova.nome, nova.id);
            }
        } else {
            printf("Opção inválida. Tenta de novo.\n");
        }
    }

    liberarFila(&fila);
    return 0;
}
