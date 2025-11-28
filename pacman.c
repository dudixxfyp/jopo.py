// pacman_original_limpo.c
#include <unistd.h> // lib para o delay => usleep()
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

#ifndef H
#define H 25 // altura do mapa
#endif
#ifndef W
#define W 42 // largura do mapa
#endif
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// Mapa (mantive exatamente o seu conteúdo)
char map[H][W] = {
{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
{'#', 'x', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
{'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'O', '#'},
{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

int game_score = 0;
hero pacman;
ghost blinky;
ghost ghosts[MAX_GHOSTS]; 

// Variáveis do menu
int numFantasmas = 1;
int nivelAtual = 1;
float tempoDesdeInicio = 0.0f;
int pelletsRemaining = 0;
int jogoPausado = 0;
int resetar = 0;

static char original_map[H][W];
static void copiarMapaOriginal() {
    memcpy(original_map, map, sizeof(original_map));
}

static void restaurarMapaOriginal() {
    memcpy(map, original_map, sizeof(map));
}

static void contarPelletsIniciais() {
    int i,j; pelletsRemaining = 0;
    for (i = 0; i < H; ++i)
      for (j = 0; j < W; ++j)
        if (original_map[i][j] == '.') pelletsRemaining++;
}

// (Removi as typedef duplicadas que conflitavam com game.h)

// Mostrar o mapa.
void inicializaPosicoesPadrao() {
    // pacman
    pacman.pos[0] = 1;
    pacman.pos[1] = 1;
    pacman.face = 'x';
    pacman.direction = KEY_RIGHT;

    // fantasmas: definir até numFantasmas
    if (numFantasmas < 1) numFantasmas = 1;
    if (numFantasmas > MAX_GHOSTS) numFantasmas = MAX_GHOSTS;

    // exemplo de posições: blinky no canto inferior direito
    ghosts[0].pos[0] = 40; ghosts[0].pos[1] = 23;
    if (numFantasmas >= 2) { ghosts[1].pos[0] = 40; ghosts[1].pos[1] = 1; }
    if (numFantasmas >= 3) { ghosts[2].pos[0] = 1;  ghosts[2].pos[1] = 23; }
    if (numFantasmas >= 4) { ghosts[3].pos[0] = 1;  ghosts[3].pos[1] = 1; }

    // keep blinky variable compatible (mirror initial)
    blinky = ghosts[0];
}
void inicializaJogoCompleto() {
    game_score = 0;
    tempoDesdeInicio = 0.0f;
    resetar = 0;
    jogoPausado = 0;
    copiarMapaOriginal();
    restaurarMapaOriginal();
    contarPelletsIniciais();
    inicializaPosicoesPadrao();
}
void show_map(int pacman_pos[2], int blinky_pos[2]) {
  int i, j;

  move(0,0); // Mover cursor para a posicao 0,0 da tela

  for (i = 0; i < H; i++) {
    for (j = 0; j < W; j++) {

      if ( j == pacman_pos[0] && i == pacman_pos[1] ) { // se for a posicao do pacman colore
        addch(map[i][j] | COLOR_PAIR(1));
      } else if(j == blinky_pos[0] && i == blinky_pos[1]) { // se for a posicao do blinky
        addch(map[i][j] | COLOR_PAIR(2));
      } else { // se nao for o pacman e nenhum fantasminha
        addch(map[i][j]);
      }
    }
    addch('\n'); // quebra a linha
  }
  mvprintw(H + 1, 0, "SCORE: %d", game_score); // por fim, mostra a pontuacao
  refresh(); // e essa eh a funcao para exibir tudo na tela.
}

// Funcao para mover o pacman no mapa (mantive sua lógica original, mas sem duplicar typedefs)
void movae_pacman(int direction, int *x, int *y, char face) {

  switch ( direction ) {
    case KEY_UP:
      if ( map[*y - 1][*x] != '#' ) {
        map[*y][*x] = ' ';
        if ( map[*y - 1][*x] == '.' ) {
          game_score += 10;
        }
        map[--*y][*x] = face;
      }
      break;
    case KEY_DOWN:
      if (map[*y + 1][*x] != '#') {
        map[*y][*x] = ' ';
        if ( map[*y + 1][*x] == '.' ) {
          game_score += 10;
        }
        map[++*y][*x] = face;
      }
      break;
    case KEY_LEFT:
      if (map[*y][*x - 1] != '#') {
        map[*y][*x] = ' ';
        if ( map[*y][*x - 1] == '.' ) {
          game_score += 10;
        }
        map[*y][--*x] = face;
      }
      break;
    case KEY_RIGHT:
      if (map[*y][*x + 1] != '#') {
        map[*y][*x] = ' ';
        if ( map[*y][*x + 1] == '.' ) {
          game_score += 10;
        }
        map[*y][++*x] = face;
      }
      break;
  }
}

// Movimentacao do Blinky (mantive sua função original)
char blinky_last_char = '.';
int blinky_last_pos = -1;

void movae_blinky(int *x, int *y, int pacman_pos[2]) {
  int dx = pacman_pos[0] - *x;
  int dy = pacman_pos[1] - *y;

  if (abs(dx) >= abs(dy)) {
    if (dx < 0 && map[*y][*x - 1] != '#') { map[*y][*x] = '.'; map[*y][--*x] = 'O'; return; }
    if (dx > 0 && map[*y][*x + 1] != '#') { map[*y][*x] = '.'; map[*y][++*x] = 'O'; return; }
  }
  if (dy < 0 && map[*y - 1][*x] != '#') { map[*y][*x] = '.'; map[--*y][*x] = 'O'; return; }
  if (dy > 0 && map[*y + 1][*x] != '#') { map[*y][*x] = '.'; map[++*y][*x] = 'O'; return; }

  int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
  for (int k = 0; k < 4; ++k) {
    int r = rand() % 4;
    int nx = *x + dirs[r][0];
    int ny = *y + dirs[r][1];
    if (nx >= 0 && nx < W && ny >= 0 && ny < H && map[ny][nx] != '#') {
      map[*y][*x] = '.';
      *x = nx; *y = ny;
      map[*y][*x] = 'O';
      return;
    }
  }
}

// wrapper para a função que o seu código chamava (para manter compatibilidade)
void movae_blinky_like(int *x, int *y, int pacman_pos[2]) {
    movae_blinky(x,y,pacman_pos);
}

// chama movimentação para todos os fantasmas
void movae_fantasmas() {
  for (int g = 0; g < numFantasmas; ++g) {
    movae_blinky_like(&ghosts[g].pos[0], &ghosts[g].pos[1], pacman.pos);
  }
  blinky = ghosts[0];
}

// MAIN (corrigi a duplicação aqui – tinha dois mains)
int main() {
  int key;

  srand((unsigned) time(NULL));

  copiarMapaOriginal();
  inicializaJogoCompleto();

  initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  nodelay(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  show_map(pacman.pos, blinky.pos);

  time_t start_time = time(NULL);

  do {
    if (resetar) {
      inicializaJogoCompleto();
      show_map(pacman.pos, blinky.pos);
    }

    if (jogoPausado) {
      nodelay(stdscr, FALSE);
      endwin();
      mostrarMenu();
      initscr();
      keypad(stdscr, TRUE);
      curs_set(0);
      nodelay(stdscr, TRUE);
      start_color();
      init_pair(1, COLOR_YELLOW, COLOR_BLACK);
      init_pair(2, COLOR_RED, COLOR_BLACK);
      show_map(pacman.pos, blinky.pos);
      continue;
    }

    key = getch();
    if (key != ERR) {
      if (key == 'p' || key == 'P') {
        jogoPausado = 1;
        continue;
      } else {
        pacman.direction = key;
      }
    }

    movae_pacman(pacman.direction, &pacman.pos[0], &pacman.pos[1], pacman.face);
    movae_fantasmas();

    show_map(pacman.pos, blinky.pos);

    if (pacman.direction == KEY_UP || pacman.direction == KEY_DOWN) usleep(130000);
    else usleep(85000);

    tempoDesdeInicio = (float)(time(NULL) - start_time);

  } while (key != 'e');

  curs_set(1);
  endwin();
  return 0;
}
