#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Snake.cpp"
#include "Fruit.cpp"

using namespace std;

bool walls;
bool gameOver;
const int width = 20;
const int height = 20;
Snake snake;
Fruit fruit;
int score;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;

void Setup() {
    srand((unsigned int) time(0));
    gameOver = false;
    dir = STOP;
    snake.setX(width / 2);
    snake.setY(height / 2);
    fruit.setX(rand() % width);
    fruit.setY(rand() % height);
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
        if (system("cls")) system("clear");
        for (int i = 0; i  < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";

                if (i == snake.getY() && j == snake.getX())
                    cout << "O";
                else if (i == fruit.getY() && j == fruit.getX())
                    cout << "X";
                else {
                    bool print = false;
                    for (int k = 0; k < snake.getTailLength(); k++) {
                        if (snake.tail[k].getX() == j && snake.tail[k].getY() == i) {
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
        cout << "Copyright Yan-Luca L." << flush;
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
        int prevX = snake.tail[0].getX();
        int prevY = snake.tail[0].getY();
        int prev2X, prev2Y;
        snake.tail[0].setX(snake.getX());
        snake.tail[0].setY(snake.getY());
        for (int i = 1; i < snake.getTailLength(); i++) {
            prev2X = snake.tail[i].getX();
            prev2Y = snake.tail[i].getY();
            snake.tail[i].setX(prevX);
            snake.tail[i].setY(prevY);
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch (dir) {
            case LEFT:
                snake.setX(snake.getX() - 1);
                Sleep(150);
                break;
            case RIGHT:
                snake.setX(snake.getX() + 1);
                Sleep(150);
                break;
            case UP:
                snake.setY(snake.getY() - 1);
                Sleep(250);
                break;
            case DOWN:
                snake.setY(snake.getY() + 1);
                Sleep(250);
                break;
            default:
                break;
        }
        if (snake.getX() > width || snake.getX() < 0 || snake.getY() > height || snake.getY() < 0) {
            if (walls) {
                GameOver();
            } else {
                if (snake.getX() >= width)
                    snake.setX(0);
                else if (snake.getX() < 0)
                    snake.setX(width - 1);

                if (snake.getY() >= height)
                    snake.setY(0);
                else if (snake.getY() < 0)
                    snake.setY(height - 1);
            }
        }

        for (int i = 0; i < snake.getTailLength(); i++)
            if(snake.tail[i].getX() == snake.getX() && snake.tail[i].getY() == snake.getY())
                GameOver();

        if (snake.getX() == fruit.getX() && snake.getY() == fruit.getY()) {
            srand((unsigned int) time(0));
            score += 1;
            fruit.setX(rand() % width);
            fruit.setY(rand() % height);
            snake.setTailLength(snake.getTailLength() + 1);
        }
    }
}
