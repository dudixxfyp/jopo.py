#ifndef FANTASMA_H
#define FANTASMA_H

typedef struct {
    int linha;             
    int coluna;           
    int vivo;              
    int vulneravel;        
    int tempoVulneravel;   
    int velocidade;        
} Fantasma;

typedef struct NoFantasma {
    Fantasma f;
    struct NoFantasma *prox;
} NoFantasma;

typedef struct {
    NoFantasma *inicio;
} ListaFantasmas;

void inicializarListaFantasmas(ListaFantasmas *L);

void inserirFantasma(ListaFantasmas *L, Fantasma f);

void moverFantasmas(ListaFantasmas *L, char **mapa, int linhas, int colunas);

void ativarModoVulneravel(ListaFantasmas *L);

void atualizarTemporizadorVulneravel(ListaFantasmas *L);

int verificarColisoes(ListaFantasmas *L, int pacLinha, int pacColuna);

#endif
