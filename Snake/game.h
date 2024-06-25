#ifndef GAME_H
#define GAME_H

#include <Windows.h>

#define SNAKE_LENGTH 400
#define CELL_SIZE 20
#define WINDOW_SIZE 400
#define HEIGHT_MARGIN 41
#define WIDTH_MARGIN 18

struct Point {
    int x, y;
};

extern Point snake[SNAKE_LENGTH];
extern int snakeLength;
extern Point food;
extern int direction;
extern int gameRunning;

void InitializeGame();
void MoveSnake();
void DrawGame(HDC hdc);
void GameOver();

#endif
