#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"   // para as declarações extern

// ------------------ PILHA ------------------
void initPilha(Pilha *p) {
    p->topo = NULL;
}

void push(Pilha *p, char acao) {
    Node *n = malloc(sizeof(Node));
    if (!n) return;
    n->acao = acao;
    n->prox = p->topo;
    p->topo = n;
}

char pop(Pilha *p) {
    if (p->topo == NULL) return '\0';
    Node *n = p->topo;
    char acao = n->acao;
    p->topo = n->prox;
    free(n);
    return acao;
}

int pilhaVazia(Pilha *p) {
    return p->topo == NULL;
}

// ------------------ SALVAR ------------------

int salvarJogo() {
    FILE *f = fopen("savegame.bin", "wb");
    if (!f) return 0;

    // salva pacman (struct hero)
    fwrite(&pacman, sizeof(hero), 1, f);

    // salva blinky (exemplo). Se tiver vetor de fantasmas, salve todos.
    fwrite(&blinky, sizeof(ghost), 1, f);

    // salva pontuação e variáveis do jogo
    fwrite(&game_score, sizeof(int), 1, f);
    fwrite(&numFantasmas, sizeof(int), 1, f);
    fwrite(&nivelAtual, sizeof(int), 1, f);
    fwrite(&tempoDesdeInicio, sizeof(float), 1, f);
    fwrite(&pelletsRemaining, sizeof(int), 1, f);

    // opcional: salvar o mapa (25x42 chars)
    fwrite(map, sizeof(char), H * W, f);

    fclose(f);
    return 1;
}

// ------------------ CARREGAR ------------------
int carregarJogo() {
    FILE *f = fopen("savegame.bin", "rb");
    if (!f) return 0;

    fread(&pacman, sizeof(hero), 1, f);
    fread(&blinky, sizeof(ghost), 1, f);
    fread(&game_score, sizeof(int), 1, f);
    fread(&numFantasmas, sizeof(int), 1, f);
    fread(&nivelAtual, sizeof(int), 1, f);
    fread(&tempoDesdeInicio, sizeof(float), 1, f);
    fread(&pelletsRemaining, sizeof(int), 1, f);

    // recarrega mapa
    fread(map, sizeof(char), H * W, f);

    fclose(f);
    return 1;
}

// ------------------ MENU VIA GETCHAR ------------------
// O menu usa as variáveis globais definidas pelo pacman.c
// Quando o usuário escolher voltar (V), o menu deve alterar jogoPausado = 0;
// Quando o usuário escolher Novo (N), setar resetar = 1; a pessoa 1 deve reagir.
void mostrarMenu() {
    static Pilha historico;
    static int pilha_inicializada = 0;
    if (!pilha_inicializada) { initPilha(&historico); pilha_inicializada = 1; }

    printf("\n================ MENU DO JOGO ================\n");
    printf("N - Novo Jogo\n");
    printf("S - Salvar Jogo\n");
    printf("C - Carregar Jogo\n");
    printf("V - Voltar ao Jogo\n");
    printf("Q - Sair\n");

    if (!pilhaVazia(&historico)) {
        printf("\nÚltima ação: %c\n", historico.topo->acao);
    }

    printf("Escolha uma opcao: ");
    int opcao = getchar();

    // limpa buffer até newline
    while (getchar() != '\n');

    switch (opcao) {
        case 'n': case 'N':
            push(&historico, 'N');
            resetar = 1; // Pessoa 1 deve reinicializar o jogo quando ler resetar == 1
            break;

        case 's': case 'S':
            push(&historico, 'S');
            if (salvarJogo()) printf("\nJogo salvo!\n");
            else printf("\nErro ao salvar!\n");
            break;

        case 'c': case 'C':
            push(&historico, 'C');
            if (carregarJogo()) printf("\nJogo carregado!\n");
            else printf("\nNenhum save encontrado!\n");
            break;

        case 'v': case 'V':
            push(&historico, 'V');
            jogoPausado = 0; // Pessoa 1 deve observar isso e voltar ao loop
            break;

        case 'q': case 'Q':
            push(&historico, 'Q');
            printf("\nSaindo do jogo...\n");
            exit(0);
            break;

        default:
            printf("\nOpcao invalida!\n");
            break;
    }
}
