#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Struct que representa cada peça:
    - nome: tipo da peça ('I', 'O', 'T', 'L')
    - id: identificador único
*/
typedef struct {
    char nome;
    int id;
} Peca;

#define TAM 5  // Tamanho fixo da fila

// Fila circular
Peca fila[TAM];
int inicio = 0;
int fim = 0;
int quantidade = 0;
int proximoID = 0; // usado para gerar IDs únicos

// ---------- Função que gera automaticamente uma nova peça ----------
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4]; // tipo aleatório
    nova.id = proximoID++;         // ID único

    return nova;
}

// ---------- Inserir peça (enqueue) ----------
void enqueue() {
    if (quantidade == TAM) {
        printf("Fila cheia! Nao e possivel inserir nova peca.\n");
        return;
    }

    fila[fim] = gerarPeca(); // gera peça automaticamente
    fim = (fim + 1) % TAM;   // movimento circular
    quantidade++;

    printf("Peca adicionada!\n");
}

// ---------- Remover peça (dequeue) ----------
void dequeue() {
    if (quantidade == 0) {
        printf("Fila vazia! Nenhuma peca para jogar.\n");
        return;
    }

    printf("Jogando a peca: [%c %d]\n", fila[inicio].nome, fila[inicio].id);

    inicio = (inicio + 1) % TAM; // avança circularmente
    quantidade--;
}

// ---------- Exibir fila ----------
void exibirFila() {
    printf("\nFila de pecas:\n");

    if (quantidade == 0) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = inicio;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM;
    }

    printf("\n");
}

int main() {
    srand(time(NULL)); // gera peças aleatórias

    // Inicializando a fila com 5 peças
    for (int i = 0; i < TAM; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirFila();

        printf("\n--- MENU ---\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            dequeue();
        }
        else if (opcao == 2) {
            enqueue();
        }
        else if (opcao == 0) {
            printf("Encerrando...\n");
        }
        else {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
