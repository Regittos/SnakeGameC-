#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 70
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 30
short int matrix[30][30];
using namespace std;
int snake, snakepos[2], comPos[2], score, i, j, timer;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void drawBorder()
{

    for (i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (j = 0; j < 2; j++)
        {
            gotoxy(0 + j, i);
            cout << "#";
            gotoxy(WIN_WIDTH - j, i);
            cout << "#";
        }
    }
    for (i = 0; i < WIN_WIDTH; i++)
    {
        for (j = 0; j < 2; j++)
        {
            gotoxy(i, 0 + j);
            cout << "#";
            gotoxy(i, SCREEN_HEIGHT - (1 + j));
            cout << "#";
        }
    }
}
void cPos()
{
    srand(time(NULL));
label:
    comPos[0] = (rand() % 26) + 2;
    comPos[1] = (rand() % 25) + 2;
    if (snakepos[0] == comPos[0] && snakepos[1] == comPos[1])
        goto label;
    SetConsoleTextAttribute(console, 4);
    gotoxy(comPos[0], comPos[1]);
    cout << "O";
}
void scor()
{
    if (snakepos[0] == comPos[0] && snakepos[1] == comPos[1])
    {
        score++;
        cPos();
        SetConsoleTextAttribute(console, 10);
    }
    gotoxy(WIN_WIDTH + 2, 21);
    cout << " SCORE: " << score;
}
void telaInicial()
{
    int op;
    gotoxy(15, 12);
    cout << "Selecione a Dificuldade";
    gotoxy(15, 13);
    cout << "1 Para facil";
    gotoxy(15, 14);
    cout << "2 Para nao tao facil";
    gotoxy(15, 15);
    cout << "3 Para medio";
    gotoxy(15, 16);
    cout << "4 Para dificil";
    gotoxy(15, 17);
    cout << "5 Para dificuldade dark souls";
    cin >> op;
    switch (op)
    {
    case 1:
        timer = 300;
        break;
    case 2:
        timer = 150;
        break;
    case 3:
        timer = 75;
        break;
    case 4:
        timer = 50;
        break;
    case 5:
        timer = 20;
        break;
    }
}
void gameover()
{
    SetConsoleTextAttribute(console, 4); // muda a cor corrente do texto no console
    timer = 300;
    system("cls");
    gotoxy(15, 12);
    cout << " ____    ____    __ __    _____     ______             ____  ___    ||";
    Sleep(timer);
    gotoxy(15, 13);
    cout << "|       |    |  |  |  |   |         |    |  \\      /  |      |  \\   ||";
    Sleep(timer);
    gotoxy(15, 14);
    cout << "|  __   |____|  |  |  |   |____     |    |   \\    /   |____  |__/   ||";
    Sleep(timer);
    gotoxy(15, 15);
    cout << "|    |  |    |  |  |  |   |         |    |    \\  /    |      |\\     ||";
    Sleep(timer);
    gotoxy(15, 16);
    cout << "|____|  |    |  |  |  |   |____     |____|     \\/     |____  | \\    OO" << endl;
    cout << "                                     SCORE: " << score;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    Sleep(timer);
    exit(1);
}
void play()
{
    SetConsoleTextAttribute(console, 7);
    system("cls");
    telaInicial();
    system("cls");
    drawBorder();
    snakepos[0] = SCREEN_HEIGHT / 2;
    snakepos[1] = WIN_WIDTH / 2;
    gotoxy(WIN_WIDTH + 7, 2);
    cout << "Snake Game";
    gotoxy(WIN_WIDTH + 6, 4);
    cout << "----------";
    gotoxy(WIN_WIDTH + 6, 6);
    cout << "----------";
    gotoxy(WIN_WIDTH + 7, 12);
    cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13);
    cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14);
    cout << " A Key - Left";
    gotoxy(WIN_WIDTH + 2, 15);
    cout << " D Key - Right";
    gotoxy(WIN_WIDTH + 2, 16);
    cout << " w Key - Up";
    gotoxy(WIN_WIDTH + 2, 17);
    cout << " s Key - Down";
    gotoxy(WIN_WIDTH + 2, 21);
    cout << " SCORE: " << score;
    cPos();
    SetConsoleTextAttribute(console, 10);
    gotoxy(snakepos[0], snakepos[1]);
    cout << "A";
    char ch = 0, ca, d;
    while (1)
    {
        if (kbhit()) //verificar se há uma versão dessa função na windows.h
            ca = getch();
        if (ca == 'a' || ca == 'd' || ca == 'w' || ca == 's' || ca == 27)
        {
            if (!(ca == 'a' && ch == 'd') && !(ca == 'w' && ch == 's') && !(ca == 'd' && ch == 'a') && !(ca == 's' && ch == 'w'))
                ch = ca;
        }
        if (ch != 0)
        {
            for (i = 0; i < 30; i++)
            {
                for (j = 0; j < 30; j++)
                {
                    if (matrix[i][j] == 1)
                    {
                        gotoxy(j, i);
                        cout << " ";
                        matrix[i][j] = 0;
                    }
                    else if (matrix[i][j] > 1)
                        matrix[i][j]--;
                    if (snakepos[0] == j && snakepos[1] == i && matrix[i][j] != 0)
                        gameover();
                    else if (snakepos[0] == j && snakepos[1] == i)
                        matrix[i][j] = score + 1;
                }
            }
        }
        if (ch == 'a')
        {
            if (snakepos[0] >= 2)
                snakepos[0]--;
            d = '<';
        }
        else if (ch == 'd')
        {
            if (snakepos[0] <= 28)
                snakepos[0]++;
            d = '>';
        }
        else if (ch == 'w')
        {
            if (snakepos[1] >= 2)
                snakepos[1]--;
            d = 'A';
        }
        else if (ch == 's')
        {
            if (snakepos[1] <= 27)
                snakepos[1]++;
            d = 'V';
        }
        else if (ch == 27)
            break;
        gotoxy(snakepos[0], snakepos[1]);
        cout << d;
        if (snakepos[0] < 2 || snakepos[0] > 28 || snakepos[1] < 2 || snakepos[1] > 27)
            gameover();
        scor();

        Sleep(timer);
    }
}

int main()
{
    play();
}
