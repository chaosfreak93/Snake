#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool walls = false;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;

void Setup() {
    srand((unsigned int) time(0));
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void GameOver() {
    gameOver = true;
    Sleep(75);
    system("cls");
    cout << "Game Over!" << endl;
    cout << "Score: " << score << endl;
}

void Draw() {
    while (!gameOver) {
        system("cls");
        for (int i = 0; i  < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";

                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX)
                    cout << "X";
                else {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i  < width + 2; i++)
            cout << "#";
        cout << endl;
        cout << "Score: " << score << endl;
        cout << "Copyright Yan-Luca L." << endl;
    }
}

void Input() {
    while (!gameOver) {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                    dir = LEFT;
                    break;
                case 'd':
                    dir = RIGHT;
                    break;
                case 'w':
                    dir = UP;
                    break;
                case 's':
                    dir = DOWN;
                    break;
                case 'x':
                    GameOver();
                    break;
            }
        }
    }
}

void Logic() {
    while (!gameOver) {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < nTail; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch (dir) {
            case LEFT:
                x--;
                Sleep(150);
                break;
            case RIGHT:
                x++;
                Sleep(150);
                break;
            case UP:
                y--;
                Sleep(150);
                break;
            case DOWN:
                y++;
                Sleep(150);
                break;
            default:
                break;
        }
        if (x > width || x < 0 || y > height || y < 0) {
            if (walls) {
                GameOver();
            } else {
                if (x >= width)
                    x = 0;
                else if (x < 0)
                    x = width - 1;

                if (y >= height)
                    y = 0;
                else if (y < 0)
                    y = height - 1;
            }
        }

        for (int i = 0; i < nTail; i++)
            if(tailX[i] == x && tailY[i] == y)
                GameOver();

        if (x == fruitX && y == fruitY) {
            srand((unsigned int) time(0));
            score += 1;
            fruitX = rand() % width;
            fruitY = rand() % height;
            nTail++;
        }
    }
}
