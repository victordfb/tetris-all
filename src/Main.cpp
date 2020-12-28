#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <vector>
#include <algorithm>
#include <ncurses.h>

using namespace std;

#define ITERMAX 10000

const int fieldWidth = 12;
const int fieldHeight = 18;
const int fieldX = 15;
const int fieldY = 4;
const int initialPosX = fieldX;
const int initialPosY = fieldY - 1;
const char noneSpace = ' ';

int readMatrix(int& x, int& y)
{
    return y * 4 + x;
}

void freeze(int currentX, int currentY, string& currentTetro, vector<string>& layers)
{
    for(int y=3; y >= 0; y--)
    {
        int i = fieldHeight - (currentY + y);
        if(!(layers.size() > i))
        {
            layers.push_back(string(10, noneSpace));
        }
        for(int x=0; x < 4; x++)
        {
            char a = currentTetro[readMatrix(x, y)];
            if(a != noneSpace)
                layers[i-1][(currentX - 1) + x] = a;
        }
    }
}

bool detectColision(int currentY, int currentX, string& tetromino, vector<string>& layers)
{
    for(int y=3; y >= 0; y--)
        for(int x=0; x < 4; x++)
        {
            if(currentY + y >= fieldHeight
                && tetromino[readMatrix(x, y)] != noneSpace)
            {
                return true;
            }
            for(int yy=layers.size() - 1; yy >= 0; yy--)
            {
                //Linha do layers é a mesma da tetromino?
                if(fieldHeight - (yy + 1) == currentY + y)
                {
                    auto v = layers[yy];
                    for(int xx=0; xx < v.size(); xx++)
                        if(xx == currentX + (x - 1) 
                            && v[xx] != noneSpace 
                            && tetromino[readMatrix(x, y)] != noneSpace)
                            return true;
                }                        
            }
        }
    return false;
}

int main()
{
    string tetromino[7];
    tetromino[0] = "     OO  OO     ";
    tetromino[1] = "  O   O   O   O ";
    tetromino[2] = "      O   O  OO ";
    string field = "";
    for(int i=0; i < fieldHeight - 1; i++)
        field += "#          #";
    field += "############";
    vector<string> layers;

    initscr();
    nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

    int speed = 10;
    int tick = 0;
    int currentY = 0;
    int currentX = 0;
    int currentTetro = rand() % 3;
    int ch;

    while(true)
    {
        this_thread::sleep_for(50ms);

        ch = getch();

        if(ch == KEY_LEFT)
            currentX = max(0, currentX - 1);
        else if(ch == KEY_RIGHT)
            currentX = min(7, currentX + 1);

        for(int y = 0; y < fieldHeight; y++)
            mvprintw(fieldY + y, fieldX, field.substr(y * fieldWidth, fieldWidth).c_str());
        
        for(int y=0; y < layers.size(); y++)
            mvprintw(fieldY + fieldHeight - (y + 2), fieldX + 1, layers[y].c_str());

        for(int y = 0; y < 4; y++)
            for(int x = 0; x < 4; x++)
            {
                char a = tetromino[currentTetro][readMatrix(x, y)];
                if(a != ' ')
                    mvaddch(initialPosY + currentY + y, initialPosX + currentX + x, a);
            }

        if(tick++ == speed)
        {
            currentY++;
            tick = 0;
        }

        if(detectColision(currentY + 1, currentX, tetromino[currentTetro], layers))
        {
            if(currentY == 0)
                break;
            
            freeze(currentX, currentY, tetromino[currentTetro], layers);
            currentY = 0;
            currentTetro = rand() % 3;
        }

        refresh();
    }
    nodelay(stdscr, FALSE);
    mvprintw(24, 5, "Obrigado por nos escolher! Até mais...");
    getch();
	endwin();

	return 0;
}