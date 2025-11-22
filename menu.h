#ifndef MENU_H
#define MENU_H

#include "game.h"  
// game.h  feito pela pessoa 1
typedef struct Node {
    char acao;
    struct Node *prox;
} Node;

typedef struct {
    Node *topo;
} Pilha;

// funções da pilha
void initPilha(Pilha *p);
void push(Pilha *p, char acao);
char pop(Pilha *p);
int pilhaVazia(Pilha *p);

void mostrarMenu(GameState *g, Pilha *historico);
int salvarJogo(GameState *g);
int carregarJogo(GameState *g);

#endif
