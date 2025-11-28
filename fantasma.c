#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fantasma.h"

void inicializarListaFantasmas(ListaFantasmas *L) {
    L->inicio = NULL;
}

void liberarListaFantasmas(ListaFantasmas *L) {
    NoFantasma *atual = L->inicio;
    while (atual) {
        NoFantasma *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    L->inicio = NULL;
}

void inserirFantasma(ListaFantasmas *L, Fantasma f) {
    NoFantasma *novo = malloc(sizeof(NoFantasma));
    if (!novo) return;

    novo->f = f;
    novo->prox = L->inicio;
    L->inicio = novo;
}

int podeMover(char **mapa, int l, int c, int maxL, int maxC) {
    if (l < 0 || l >= maxL) return 0;
    if (c < 0 || c >= maxC) return 0;
    return (mapa[l][c] != '#'); 
}

void moverFantasmas(ListaFantasmas *L, char **mapa, int linhas, int colunas) {
    int movL[4] = {-1, 1, 0, 0};
    int movC[4] = {0, 0, -1, 1};

    for (NoFantasma *atual = L->inicio; atual; atual = atual->prox) {

        if (!atual->f.vivo) continue;

        int dir = rand() % 4;
        int nl = atual->f.linha + movL[dir];
        int nc = atual->f.coluna + movC[dir];

        if (podeMover(mapa, nl, nc, linhas, colunas)) {
            atual->f.linha = nl;
            atual->f.coluna = nc;
        }
    }
}

void ativarModoVulneravel(ListaFantasmas *L) {
    for (NoFantasma *atual = L->inicio; atual; atual = atual->prox) {
        atual->f.vulneravel = 1;
        atual->f.tempoVulneravel = 8;
    }
}

void atualizarTemporizadorVulneravel(ListaFantasmas *L) {
    for (NoFantasma *atual = L->inicio; atual; atual = atual->prox) {
        if (atual->f.vulneravel) {
            atual->f.tempoVulneravel--;
            if (atual->f.tempoVulneravel <= 0)
                atual->f.vulneravel = 0;
        }
    }
}

int verificarColisoes(ListaFantasmas *L, int pacL, int pacC) {
    for (NoFantasma *atual = L->inicio; atual; atual = atual->prox) {

        if (!atual->f.vivo) continue;

        if (atual->f.linha == pacL && atual->f.coluna == pacC) {

            // Pac-Man come fantasma
            if (atual->f.vulneravel) {
                atual->f.vivo = 0;
                return 2;
            }

            // Fantasma mata Pac-Man
            return 1;
        }
    }
    return 0;
}
