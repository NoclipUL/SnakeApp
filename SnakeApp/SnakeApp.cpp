// SnakeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "cSnake.h"
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

bool gameOver;
const int cao = 20;
const int rong = 20;

void khungTroChoi(const cSnake& snake)
{
	system("cls");

	for (int i = 0; i < rong + 2; i++)
	{
			std::cout << "#";
	}
	std::cout << std::endl;
	for (int y = 0; y < cao; y++)
	{
		std::cout << "#";

		for (int x = 0; x < rong; x++)
		{
			bool printed = false;
			const std::vector<TD>& body = snake.toaDoThanRan();

			for (int i = 0; i < (int)body.size(); i++)
			{
				if (body[i].x == x && body[i].y == y)
				{
					if (i == 0)
					{
						std::cout << "O";
					}
					else
					{
						std::cout << char(219);
					}
					printed = true;
					break;
				}
			}
			if (!printed)
				std::cout << " ";
		}
		std::cout << "#" << std::endl;
	}
	for (int i = 0; i < rong + 2; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Diem so: " << std::endl;
}

void Input(cSnake& snake)
{
	if (_kbhit())
	{
		char key = _getch();

		switch (key)
		{
		case 'a':
		case 'A':
			snake.doiHuong(1);
			break;
		case 'd':
		case 'D':
			snake.doiHuong(2);
			break;
		case 'w':
		case 'W':
			snake.doiHuong(3);
			break;
		case 's':
		case 'S':
			snake.doiHuong(4);
			break;
		case 'x':
		case 'X':
			gameOver = true;
			break;
		}
	}
}

void gameRules(cSnake& snake)
{
	snake.diChuyen();

	TD dauRan = snake.toaDoDauRan();
	if (dauRan.x < 0 || dauRan.x >= rong || dauRan.y < 0 || dauRan.y >= cao)
	{
		gameOver = true;
		return;
	}
}

void runGame(cSnake& snake)
{
	while (!gameOver)
	{
		khungTroChoi(snake);
		Input(snake);
		gameRules(snake);
		Sleep(200);
	}
	khungTroChoi(snake);
	std::cout << "Game Over!!!" << std::endl;

}

int main()
{
	srand((unsigned)time(0));
	cSnake snake(1,1);
	runGame(snake);
	return 0;
}
