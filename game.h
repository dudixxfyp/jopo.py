#ifndef GAME_H
#define GAME_H

// Este header é uma "ponte" entre o código da Pessoa 1 (pacman.c / mapa.c) e o menu (Pessoa 4).
// Ele deve ser incluído tanto em pacman.c quanto em menu.c (ou basta em pacman.c definir
// as variáveis e em menu.c declará-las como extern).

// Se pacman.c já define os tipos `hero` e `ghost`, comente as typedefs duplicadas.
// Se não existir um header que declare esses typedefs, cole aqui as definições.

#ifndef HERO_GHOST_TYPES
#define HERO_GHOST_TYPES
typedef struct _TAG_hero {
    int pos[2];      // pos[0] = x (coluna), pos[1] = y (linha)
    int direction;
    char face;
} hero;

typedef struct _TAG_ghost {
    int pos[2];
} ghost;
#endif

// constantes do mapa (iguais às do pacman.c)
#ifndef H
#define H 25
#endif
#ifndef W
#define W 42
#endif

// Variáveis definidas (DEFINIÇÔES) em pacman.c:
//   hero pacman;
//   ghost blinky; (e possivelmente outros ghosts)
//   int game_score;
//   char map[H][W];
// Para que menu.c possa usar essas variáveis, aqui colocamos as declarações extern.
//
// A Pessoa 1 (arquivo pacman.c) deve DEFINIR estas variáveis (sem extern), por exemplo:
//   hero pacman;
//   ghost blinky;
//   int game_score = 0;
//   char map[H][W] = { ... };
//
// Se a Pessoa 1 já tem nomes diferentes (por exemplo: 'hero pacman' com outro nome ou várias ghosts),
// ajuste aqui para bater com os nomes reais.

extern hero pacman;        // definido em pacman.c
extern ghost blinky;       // definido em pacman.c (ou outros ghosts)
extern int game_score;     // definido em pacman.c
extern char map[H][W];     // definido em pacman.c

// Variáveis auxiliares que o menu usa e que podem ser criadas na Pessoa 1 (se ainda não existir):
// A Pessoa 1 deve adicionar as definições (não extern) em pacman.c:
//    int numFantasmas = 1;         // por exemplo
//    int nivelAtual = 1;
//    float tempoDesdeInicio = 0.0f;
//    int pelletsRemaining = 0;     // ou calcular quando carregar o mapa
//    int jogoPausado = 0;
//    int resetar = 0;

extern int numFantasmas;
extern int nivelAtual;
extern float tempoDesdeInicio;
extern int pelletsRemaining;
extern int jogoPausado;
extern int resetar;

#endif // GAME_H
