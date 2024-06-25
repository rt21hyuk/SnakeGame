#include <Windows.h>
#include "game.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;

    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WndProc;
    WndClass.lpszClassName = L"SnakeGame";
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&WndClass);

    hWnd = CreateWindowEx(0, WndClass.lpszClassName, L"Snake Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_SIZE+WIDTH_MARGIN, WINDOW_SIZE+ HEIGHT_MARGIN, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    InitializeGame();

    while (GetMessage(&Message, NULL, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 100, NULL);
        break;
    case WM_TIMER:
        if (gameRunning)
        {
            MoveSnake();
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_KEYDOWN:
        if (gameRunning)
        {
            switch (wParam)
            {
            case VK_UP:
            case VK_DOWN:
            case VK_LEFT:
            case VK_RIGHT:
                direction = wParam;
                break;
            }
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawGame(hdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, iMessage, wParam, lParam);
    }
    return 0;
}
