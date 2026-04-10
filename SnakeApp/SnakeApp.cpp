// Snake game — Windows only (MSVC console: Windows.h, conio.h).
//

#include <iostream>
#include "cSnake.h"
#include <cstdlib>
#include <ctime>
#include <random>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <conio.h>

static void clearScreen()
{
	system("cls");
}

static void sleepMs(unsigned ms)
{
	Sleep(ms);
}

bool gameOver;
const int cao = 30;
const int rong = 70;

// Cang nho ran di chuyen cang nhanh/muot (ms moi buoc).
const int tocDoKhungHinhMs = 95;

void khungTroChoi(const cSnake& snake, const cFood& food, int diemSo)
{
	clearScreen();

	const TD foodPos = food.toaDoFood();

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
						std::cout << "o";
					}
					else
					{
						std::cout << "o";
					}
					printed = true;
					break;
				}
			}
			if (!printed && foodPos.x == x && foodPos.y == y)
				std::cout << "*";
			else if (!printed)
				std::cout << " ";
		}
		std::cout << "#" << std::endl;
	}
	for (int i = 0; i < rong + 2; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Diem so: " << diemSo << std::endl;
}

void Input(cSnake& snake)
{
	for (;;)
	{
		if (!_kbhit())
			break;
		const char key = static_cast<char>(_getch());

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
			return;
		default:
			break;
		}
	}
}


static bool trenThanRan(const cSnake& snake, int x, int y)
{
	for (const TD& p : snake.toaDoThanRan())
	{
		if (p.x == x && p.y == y)
			return true;
	}
	return false;
}

void randomFood(cFood& food, const cSnake& snake)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, rong - 1);
	std::uniform_int_distribution<> dis2(0, cao - 1);

	int x = 0;
	int y = 0;
	do
	{
		x = dis(gen);
		y = dis2(gen);
	} while (trenThanRan(snake, x, y));

	food.datViTri(x, y);
}

void gameRules(cSnake& snake, cFood& food, int& diemSo)
{
	snake.diChuyen();

	TD dauRan = snake.toaDoDauRan();
	if (dauRan.x < 0 || dauRan.x >= rong || dauRan.y < 0 || dauRan.y >= cao)
	{
		gameOver = true;
		return;
	}

	TD foodPos = food.toaDoFood();
	if (dauRan.x == foodPos.x && dauRan.y == foodPos.y)
	{
		diemSo++;
		snake.phatTrien();
		randomFood(food, snake);
	}
}

void runGame(cSnake& snake, cFood& food)
{
	gameOver = false;
	int diemSo = 1;

	while (!gameOver)
	{
		Input(snake);
		if (gameOver)
			break;
		gameRules(snake, food, diemSo);
		khungTroChoi(snake, food, diemSo);
		sleepMs(static_cast<unsigned>(tocDoKhungHinhMs));
	}
	khungTroChoi(snake, food, diemSo);
	std::cout << "Game Over!!!" << std::endl;
}

void randomSnake(cSnake& snake)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, rong - 1);
	std::uniform_int_distribution<> dis2(0, cao - 1);

	snake.datViTriDau(dis(gen), dis2(gen));
}

void printSnake(cSnake snake)
{
	std::cout << snake.toaDoDauRan().x << " " << snake.toaDoDauRan().y << std::endl;
}

int main()
{
	srand((unsigned)time(0));
	cSnake snake;
	cFood food;
	randomSnake(snake);
	randomFood(food, snake);
	runGame(snake, food);
	return 0;
}
