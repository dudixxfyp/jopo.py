#include <stdio.h>
#include <stdlib.h>
#include "menu.h"   // menu.h já inclui game.h, então não precisa incluir game.h aqui

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

    if (numFantasmas < 0) numFantasmas = 0;
    if (numFantasmas > MAX_GHOSTS) numFantasmas = MAX_GHOSTS;

    // 1. salva Pac-Man
    fwrite(&pacman, sizeof(hero), 1, f);

    // 2. salva número de fantasmas
    fwrite(&numFantasmas, sizeof(int), 1, f);

    // 3. salva todos os fantasmas
    fwrite(ghosts, sizeof(ghost), numFantasmas, f);

    // 4. salva variáveis do jogo
    fwrite(&game_score, sizeof(int), 1, f);
    fwrite(&nivelAtual, sizeof(int), 1, f);
    fwrite(&tempoDesdeInicio, sizeof(float), 1, f);
    fwrite(&pelletsRemaining, sizeof(int), 1, f);

    // 5. salva mapa completo
    fwrite(map, sizeof(char), H * W, f);

    fclose(f);
    return 1;
}

// ------------------ CARREGAR ------------------
int carregarJogo() {
    FILE *f = fopen("savegame.bin", "rb");
    if (!f) return 0;

    // 1. lê Pac-Man
    if (fread(&pacman, sizeof(hero), 1, f) != 1) { fclose(f); return 0; }

    // 2. lê quantidade de fantasmas
    if (fread(&numFantasmas, sizeof(int), 1, f) != 1) { fclose(f); return 0; }

    if (numFantasmas < 0) numFantasmas = 0;
    if (numFantasmas > MAX_GHOSTS) numFantasmas = MAX_GHOSTS;

    // 3. lê vetor de fantasmas
    if (fread(ghosts, sizeof(ghost), numFantasmas, f) != (size_t)numFantasmas) {
        fclose(f);
        return 0;
    }

    // 4. lê variáveis do jogo
    fread(&game_score, sizeof(int), 1, f);
    fread(&nivelAtual, sizeof(int), 1, f);
    fread(&tempoDesdeInicio, sizeof(float), 1, f);
    fread(&pelletsRemaining, sizeof(int), 1, f);

    // 5. lê mapa
    fread(map, sizeof(char), H * W, f);

    fclose(f);
    return 1;
}

// ------------------ MENU VIA GETCHAR ------------------
void mostrarMenu() {
    static Pilha historico;
    static int pilha_inicializada = 0;

    if (!pilha_inicializada) {
        initPilha(&historico);
        pilha_inicializada = 1;
    }

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

    while (getchar() != '\n'); // limpa buffer

    switch (opcao) {
        case 'n': case 'N':
            push(&historico, 'N');
            resetar = 1;    // avisar a pessoa 1 que deve reiniciar tudo
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
            jogoPausado = 0;    // volta ao loop principal
            break;

        case 'q': case 'Q':
            push(&historico, 'Q');
            printf("\nSaindo do jogo...\n");
            exit(0);

        default:
            printf("\nOpcao invalida!\n");
            break;
    }
}
