#include <stdio.h>
#include <stdlib.h>
#include "fantasma.h"

void inicializarListaFantasmas(ListaFantasmas *L) {
    L->inicio = NULL;
}

void inserirFantasma(ListaFantasmas *L, Fantasma f) {
    NoFantasma *novo = malloc(sizeof(NoFantasma));
    if (!novo) return; 
    novo->f = f;
    novo->prox = L->inicio;
    L->inicio = novo;
}

void moverFantasmas(ListaFantasmas *L, char **mapa, int linhas, int colunas) {
    for (NoFantasma *atual = L->inicio; atual; atual = atual->prox) {
        if (!atual->f.vivo) continue;  
        int novaLinha = atual->f.linha + (atual->f.vulneravel ? 1 : -1);
        if (novaLinha >= 0 && novaLinha < linhas && mapa[novaLinha][atual->f.coluna] != '#') {
            atual->f.linha = novaLinha;
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
        if (atual->f.vulneravel && --atual->f.tempoVulneravel <= 0) {
            atual->f.vulneravel = 0;
        }
    }
}

int verificarColisoes(ListaFantasmas *L, int pacLinha, int pacColuna) {
    for (NoFantasma *atual = L->inicio; atual; atual = atual->prox) {
        if (atual->f.vivo && atual->f.linha == pacLinha && atual->f.coluna == pacColuna) {
            if (atual->f.vulneravel) {
                atual->f.vivo = 0;
                return 2;
            }
            return 1; 
        }
    }
    return 0; 
}
