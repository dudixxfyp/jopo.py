#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAP_MAX_LINHAS 20
#define MAP_MAX_COLUNAS 40

Mapa *carregarMapa(const char *arquivo){
    if (!arquivo) return NULL; // 
    FILE *f = fopen(arquivo, "r");
    if (!f) { // Mensagem de erro caso o arquivo não possa ser aberto
        fprintf(stderr,"Erro ao abrir o arquivo do mapa. %s\n", arquivo); 
        return NULL;
    }

    char buffer[256]; // buffer temporario para ler cada linha do arquivo
    char *rows[MAP_MAX_LINHAS];
    int linhas = 0;

    while (fgets(buffer, sizeof(buffer), f) && linhas < MAP_MAX_LINHAS) {
        size_t len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[--len] = '\0'; // Remove nova linha 
        }

        rows[linhas] = malloc(MAP_MAX_COLUNAS + 1);
        if (!rows[linhas]) { // liberar tudo que ja foi alocado
            for (int k = 0; k < linhas; k++) {
                free(rows[k]);
            }
            fclose(f);
            return NULL;
        }
        for (int c = 0; c < MAP_MAX_COLUNAS; c++) {
            if (c < (int)len){
                rows[linhas][c] = buffer[c];}
            else {// Preencher com espaços as linhas
                rows[linhas][c] = ' '; }
        }
        rows[linhas][MAP_MAX_COLUNAS] = '\0'; 
        linhas ++;
    }
    fclose(f);

    if(linhas == 0) {
        return NULL; // erro se o arquivo do mapa estiver vazio ou sem linhas válidas.
    }
    Mapa *m = malloc (sizeof(Mapa)); // alocar estrutura do mapa dinamicamente
    if (!m) { // erro na alocação
        for (int k = 0; k < linhas; k++) {
            free(rows[k]);}
        return NULL;
    }

    m->linhas = linhas; 
    m->colunas = MAP_MAX_COLUNAS;

    m->celulas = malloc(sizeof(char*) * linhas); // alocar dinacamente matriz de celulas
    if (!m -> celulas) {
        for (int k = 0; k < linhas; k++) {
            free(rows[k]);}
        free(m);
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {
        m->celulas[i] = rows[i]; // copiar as linhas lidas para a matriz do mapa
    }
    return m;
}

// liberarMapa: liberar a memoria alocada para o mapa
void liberarMapa(Mapa *mapa){
    if (!mapa) return; // retorna se o mapa for NULL
    if (mapa->celulas) {
        for (int i = 0; i < mapa->linhas; i++) {
            free(mapa->celulas[i]);
        }
        free(mapa->celulas);
    } free(mapa);
}

// desenharMapa: Desenhar o mapa na tela usando ncurses e exibe HUD
void desenharMapa(Mapa *m, Posicao pacman, Posicao blinky, int vidas, int pontuacao, int nivel) {
    if (!m) return;

    move(0, 0); // mover o cursor para o canto superior esquerdo
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            if (i == pacman.linha && j == pacman.coluna) {
                addch(m->celulas[i][j] | COLOR_PAIR(1));
            } else if (i == blinky.linha && j == blinky.coluna) {
                addch(m->celulas[i][j] | COLOR_PAIR(2));
            } else {
                addch(m->celulas[i][j]);
            }
        }
        addch('\n');
    }

    mvprintw(m->linhas + 1, 0, "VIDAS: %d  SCORE: %d  NIVEL: %d", vidas, pontuacao, nivel);
    refresh();
}

// inicializarJogo: monta o nome mapa<N>.txt e chama carregarMapa
