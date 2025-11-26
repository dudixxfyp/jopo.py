#ifndef MENU_H
#define MENU_H

#include "game.h"   // importa pacman, ghosts[], constantes, variáveis globais

// ------------------ PILHA ------------------
typedef struct Node {
    char acao;
    struct Node *prox;
} Node;

typedef struct {
    Node *topo;
} Pilha;

// Funções da pilha
void initPilha(Pilha *p);
void push(Pilha *p, char acao);
char pop(Pilha *p);
int pilhaVazia(Pilha *p);

// ------------------ MENU E SALVAMENTO ------------------
int salvarJogo();
int carregarJogo();
void mostrarMenu();

#endif // MENU_H
