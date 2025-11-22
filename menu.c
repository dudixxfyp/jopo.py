#include <stdio.h>
#include <stdlib.h>
#include "menu.h"  

//impilhar
void initPilha(Pilha *p) {
    p->topo = NULL; //topo da pilha vazio
}

void push(Pilha *p, char acao) {
    Node *n = malloc(sizeof(Node));
    n->acao = acao;
    n->prox = p->topo;
    p->topo = n;
}

//desempilhar
char pop(Pilha *p) {
    if (p->topo == NULL) return '\0';
    Node *n = p->topo;
    char acao = n->acao;
    p->topo = n->prox;
    free(n);
    return acao;
}
//confere o topo 
int pilhaVazia(Pilha *p) {
    return p->topo == NULL;
}



//pessoa 1 modificar GAME pela sua parte game iniciado, aonde você escreve fantasmas, jogo para etc...

int salvarJogo(GAME *g) {
    FILE *f = fopen("savegame.bin", "wb");
    if (!f) return 0;

    // game.h deve  criado pela pessoa  1
    fwrite(&g->pac, sizeof(Pacman), 1, f);               // Pac-Man criado pela  (Pessoa 2) 
    fwrite(&g->numFantasmas, sizeof(int), 1, f);        
    fwrite(g->fantasmas, sizeof(Fantasma), g->numFantasmas, f); // Fantasmas (Pessoa 3)
    fwrite(&g->nivelAtual, sizeof(int), 1, f);           // Nível atual do mapa (Pessoa 5)
    fwrite(&g->tempoDesdeInicio, sizeof(float), 1, f);  
    fwrite(&g->pelletsRemaining, sizeof(int), 1, f);     // Gomas restantes (Pessoa 2)

    fclose(f);
    return 1;
}

// LÊ tudo que as outras pessoas criaram no GAME


int carregarJogo(GAME *g) {
    FILE *f = fopen("savegame.bin", "rb");
    if (!f) return 0;

    fread(&g->pac, sizeof(Pacman), 1, f);
    fread(&g->numFantasmas, sizeof(int), 1, f);
    fread(g->fantasmas, sizeof(Fantasma), g->numFantasmas, f);
    fread(&g->nivelAtual, sizeof(int), 1, f);
    fread(&g->tempoDesdeInicio, sizeof(float), 1, f);
    fread(&g->pelletsRemaining, sizeof(int), 1, f);

    fclose(f);
    return 1;
}


void mostrarMenu(GameState *g, Pilha *historico) {

    printf("\n================ MENU DO JOGO ================\n");
    printf("N - Novo Jogo\n");
    printf("S - Salvar Jogo\n");
    printf("C - Carregar Jogo\n");
    printf("V - Voltar ao Jogo\n");
    printf("Q - Sair\n");

    if (!pilhaVazia(historico)) {
        printf("\nÚltima ação: %c\n", historico->topo->acao);
    }

    printf("Escolha uma opcao: ");
    char opcao = getchar();

    // Evita ENTER ser lido como nova ação
    while (getchar() != '\n');

    switch (opcao) {

      
        case 'n': case 'N':
            push(historico, 'N');
            g->resetar = 1;   // Pessoa 1 deve implementar essa lógica
            break;

        case 's': case 'S':
            push(historico, 'S');
            salvarJogo(g);
            printf("\nJogo salvo!\n");
            break;

        case 'c': case 'C':
            push(historico, 'C');
            if (carregarJogo(g))
                printf("\nJogo carregado!\n");
            else
                printf("\nNenhum save encontrado!\n");
            break;

      
        case 'v': case 'V':
            push(historico, 'V');
            g->jogoPausado = 0;   // Pessoa 1 IMPLEMENTA ISSO NO LOOP
            break;

      
        case 'q': case 'Q':
            push(historico, 'Q');
            printf("\nSaindo do jogo...\n");
            exit(0);
            break;

        default:
            printf("\nOpcao invalida!\n");
            break;
    }
}
