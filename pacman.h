#ifndef PACMAN_H
#define PACMAN_H

#include "raylib.h"
#include <stdbool.h>
#define GRID 20


typedef struct Pacman {
    Vector2 pos;
    Velocidade do flutuador ;
    Rotacão flutuante;
    Sprite Texture2D;
    Quadros INT;
    int qtSprites;
    Temporizador de flutuação;
    FPS float;
    int largSprite;
    int altSprite;
    Char Direcao;
    bool se movendo;
    int pontos;
    Int vidas;
    temporizador de flutuação Morte;  conta tempo até resetar posição após morrer
} Pacman;


Pacman CriaPacman(const char *spritePath, Vector2 startPos);
void attPacman(Pacman *p, float dt, int screenWidth, int screenHeight, Vector2 startPos);
void desenhaPacman(Pacman *p);

Vector2 DirecaoParaVetor(char d);

#endif 
