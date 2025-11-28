#include "raylib.h"
#include "pacman.h"

#define PEÇA 20
#define GRID_W 20 // 20 células no X
#define GRID_H 40 // 40 células no Y

----- MAPA 20x40 -----
    ----- MAPA 20x40 (paredes azuis, espaços e pellets) -----
    Mapa de carcaça[GRID_H][GRID_W] = {
    {'#','#','#','#','#','#','#','#'},
    {'#','x',' ',' ',' '#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ','#',' ,'#','.','#'},
    {'#',' ',' ',' ','#','.','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ','#',' ,'#','.','#'},
    {'#',' ',' ',' ','#','.','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',' ',' ',' ,' ',' ',','#',' ','#',' ,','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',' 'F',' ','#',' ,' ','#'},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#','O',' ',' ',' ',' ',' ',', ',' ',','#'},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',' ,',,' ,',',,' ,',' ',' ',' ,' ,',' ,',,',,' ,',,',,
    {'#',' ',' ',' ',',' ',' ,',,' ,',',,' ,',' ',' ',' ,' ,',' ,',,',,' ,',,',,
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',' ',' ',', 'o',' ',' ','#'},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',', 'o','#'},
    {'#',' ',' ','F',' ',' ',', ',', ',' ','#'},
    {'#',' ',' ',' ',',' ',',' ',','}, 
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#',' ',' ',' ',',' ',',' ',','},
    {'#','#','#','#','#',''#'}
};

int main(void)) {

    const int screenWidth = GRID_W * TILE;  400
    const int screenHeight = GRID_H * TILE;  800

    InitWindow (Largura da tela, Altura da tela, "TESTE DE GRADE PAC-MAN");
    SetTargetFPS(60);

    Criar Pac-Man no centro da tela
    Pacman pac = CriaPacman("assets/pacmove.png",
                            (Vetor2){ 200, 200 });

    enquanto (!JanelaDeve Fechar()) {

        float dt = GetFrameTime.();

        ----Atualização----
        attPacman(&pac, dt, screenWidth, screenHeight, (Vector2){ 200, 200 });

        ----Desenhar----
        Começando a Desenhar();
        Fundo Transparente(PRETO);

        Desenhar mapa
        para (int y = 0; y < GRID_H; y++) {
            para (int x = 0; x < GRID_W; x++) {
                Cor c = (mapa[y][x] == '#') ? AZUL: PRETO;
                DrawRectangle(
                    x * AZULEJO,
                    y * TILE,
                    AZULEJO,
                    AZULEJO,
                    c
                );
            }
        }

        Pellets Desenhar
        para (int y = 0; y < GRID_H; y++) {
            para (int x = 0; x < GRID_W; x++) {
                se (map[y][x] == '.') {
                    DrawCircle(
                        x * PEÇA + AZULEJO/2,
                        y * PEÇA + AZULEJO/2,
                        4,  pellet raio do
                        AMARELO
                    );
                }
            }
        }

        Pastilhas de Potência Desenhar
        para (int y = 0; y < GRID_H; y++) {
            para (int x = 0; x < GRID_W; x++) {
                if (map[y][x] == 'o') {
                    DrawCircle(
                        x * PEÇA + AZULEJO/2,
                        y * PEÇA + AZULEJO/2,
                        8,  Raio Do Power Pellet
                        LARANJA
                    );
                }
            }
        }

        Desenhar fantasmas
        para (int y = 0; y < GRID_H; y++) {
            para (int x = 0; x < GRID_W; x++) {
                if (map[y][x] == 'F') {
                    DrawCircle(
                        x * PEÇA + AZULEJO/2,
                        y * PEÇA + AZULEJO/2,
                        10,  raio do fantasma
                        VERMELHO
                    );
                }
            }
        }   

        Grade de desenhar (opcional)
        para (int y = 0; y <= GRID_H; y++)
            DrawLine(0, y * TILE, screenWidth, y * TILE, DARK gray);
        para (int x = 0; x <= GRID_W; x++)
            DrawLine(x * TILE, 0, x * TILE, screenHeight, DARK gray);

        desenhar Pac-Man
        desenhaPacman(&pac);

        DrawText(TextFormat("Pontos: %d", pac.pontos), 10, 10, 20, AMARELO);
        DrawText(TextFormat("Vidas: %d", pac.vidas), 10, 40, 20, AMARELO);
        se (pac.vidas <= 0) {
            DrawText("GAME OVER", Largura da tela/2 - 80, AlturaTela/2 - 20, 40, VERMELHO);
        }
        EndDrawing();
    }

    CloseWindow();
    retorno 0;
}
