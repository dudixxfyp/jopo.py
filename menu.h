#ifndef MENU_H
#define MENU_H

#include "game.h"   // expõe hero, ghost, game_score, map[][], e variáveis globais

// Pilha para histórico de ações
typedef struct Node {
    char acao;
    struct Node *prox;
} Node;

typedef struct {
    Node *topo;
} Pilha;

// pilha
void initPilha(Pilha *p);
void push(Pilha *p, char acao);
char pop(Pilha *p);
int pilhaVazia(Pilha *p);

// menu e I/O
void mostrarMenu();
int salvarJogo();     // salva os dados globais (usa externs de game.h)
int carregarJogo();   // carrega os dados e atualiza as variáveis globais

#endif // MENU_H

