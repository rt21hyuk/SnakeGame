#include "Game.h"
#include <Windows.h>
#include <stdlib.h>
#include <ctime>

Point snake[SNAKE_LENGTH];
int snakeLength;
Point food;
int direction;
int gameRunning;

void InitializeGame()
{
    srand((unsigned int)time(NULL));

    snakeLength = 2;
    snake[0].x = rand() % 20;
    snake[0].y = rand() % 20;

    snake[1].x = snake[0].x - 1;
    snake[1].y = snake[0].y;

    direction = VK_RIGHT;
    food.x = rand() % 20;
    food.y = rand() % 20;
    gameRunning = 1;

    SetTimer(NULL, 1, 1000, NULL);
}

void MoveSnake()
{
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    switch (direction)
    {
    case VK_UP:
        snake[0].y -= 1;
        break;
    case VK_DOWN:
        snake[0].y += 1;
        break;
    case VK_LEFT:
        snake[0].x -= 1;
        break;
    case VK_RIGHT:
        snake[0].x += 1;
        break;
    }

    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        snakeLength++;
        do {
            food.x = rand() % 20;
            food.y = rand() % 20;
        } while (food.x == snake[0].x && food.y == snake[0].y);
    }

    if (snake[0].x < 0 || snake[0].x >= 20 || snake[0].y < 0 || snake[0].y >= 20)
    {
        GameOver();
    }

    for (int i = 1; i < snakeLength; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            GameOver();
        }
    }
}

void DrawGrid(HDC hdc)
{
    for (int i = 0; i <= 20; i++)
    {
        MoveToEx(hdc, i * CELL_SIZE, 0, NULL);
        LineTo(hdc, i * CELL_SIZE, WINDOW_SIZE);

        MoveToEx(hdc, 0, i * CELL_SIZE, NULL);
        LineTo(hdc, WINDOW_SIZE, i * CELL_SIZE);
    }
}

void DrawGame(HDC hdc)
{
    RECT rect;
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));

    DrawGrid(hdc);

    for (int i = 0; i < snakeLength; i++)
    {
        rect.left = snake[i].x * CELL_SIZE;
        rect.top = snake[i].y * CELL_SIZE;
        rect.right = rect.left + CELL_SIZE;
        rect.bottom = rect.top + CELL_SIZE;
        FillRect(hdc, &rect, hBrush);
    }

    rect.left = food.x * CELL_SIZE;
    rect.top = food.y * CELL_SIZE;
    rect.right = rect.left + CELL_SIZE;
    rect.bottom = rect.top + CELL_SIZE;
    FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));

    DeleteObject(hBrush);
}

void GameOver()
{
    gameRunning = 0;
    KillTimer(NULL, 1);
    int choice = MessageBox(NULL, L"게임 오버! 다시 시작할까요?", L"알림", MB_YESNO | MB_ICONQUESTION);
    if (choice == IDYES)
    {
        InitializeGame();
    }
    else
    {
        PostQuitMessage(0);
    }
}
