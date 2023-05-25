#include <iostream>
#include <conio.h>
#include <random>
#include <ctime>
#include <windows.h>
#include <vector>

using namespace std;

const int width = 40;   // Width of the game board
const int height = 20;  // Height of the game board
bool gameOver;
int x, y;               // Player position
vector<int> fruitX;     // Fruit positions
vector<int> fruitY;     // Fruit positions
vector<int> fruitScores;// Scores of each fruit
int score;              // Player score
int maxScore = 10;      // Maximum score limit

struct Obstacle {
    int x;
    int y;
};
// adding obstacles using (x,y)
Obstacle obstacles[] = {
{ 4, 5 },{ 4, 6 },{ 4, 7 },{ 4, 8 },{ 4, 9 },{ 4, 10 },
    { 35, 5 },{ 35, 6 },{ 35, 7 },{ 35, 8 },{ 35, 9 },{ 35, 10 },
    { 8, 10 },
    { 12, 15 }
};
const int numObstacles = sizeof(obstacles) / sizeof(obstacles[0]);

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    // Manually add fruit positions and scores
    fruitX = { 10, 15, 20, 15, 20  };
    fruitY = { 7, 10, 15, 5, 3 };
    fruitScores = { 1, 2, 3 ,2,2 };

    score = 0;
}

void Draw()
{
    system("cls"); // Clear the screen

    // Draw the top wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // Draw the left wall

            if (i == y && j == x)
                cout << "C"; // Draw the player
            else
            {
                bool isFruit = false;
                for (int k = 0; k < fruitX.size(); k++)
                {
                    if (fruitX[k] == j && fruitY[k] == i)
                    {
                        cout << "F"; // Draw the fruit
                        isFruit = true;
                        break;
                    }
                }
                if (!isFruit)
                {
                    bool isObstacle = false;
                    for (int k = 0; k < numObstacles; k++)
                    {
                        if (obstacles[k].x == j && obstacles[k].y == i)
                        {
                            cout << "O"; // Draw the obstacle
                            isObstacle = true;
                            break;
                        }
                    }
                    if (!isObstacle)
                        cout << " ";
                }
            }

            if (j == width - 1)
                cout << "#"; // Draw the right wall
        }
        cout << endl;
    }

    // Draw the bottom wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";

	cout << endl;
    cout << "Name: BEANCA L. BARSANA" << endl;

    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
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
                gameOver = true;
                break;
        }
    }
}

void Logic()
{
    // Update the player position
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // Check for collision with walls
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    // Check for collision with fruits
    for (int k = 0; k < fruitX.size(); k++)
    {
        if (x == fruitX[k] && y == fruitY[k])
        {
            score += fruitScores[k];

            fruitX.erase(fruitX.begin() + k);
            fruitY.erase(fruitY.begin() + k);
            fruitScores.erase(fruitScores.begin() + k);

            break;
        }
    }

    // Check for collision with obstacles
    for (int k = 0; k < numObstacles; k++)
    {
        if (x == obstacles[k].x && y == obstacles[k].y)
        {
            gameOver = true;
            break;
        }
    }

    // Check for maximum score condition
    if (score >= maxScore)
    {
        cout << "You win!" << endl;
        gameOver = true;
    }
}

bool PlayAgain()
{
    char choice;
    cout << "Game over! Do you want to play again? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

int main()
{
    srand(static_cast<unsigned>(time(0))); // Initialize random seed

    bool playAgain = true;
    while (playAgain)
    {
        Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(100); // Adjust the delay value to control the game speed
        }

        playAgain = PlayAgain();
    }

    return 0;
}

