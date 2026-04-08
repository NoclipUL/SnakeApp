// SnakeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "cSnake.h"
#include <cstdlib>
#include <ctime>
#include <random>

#ifdef _WIN32
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
#else
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

static struct termios g_savedTios;
static bool g_tiosOk = false;

static void restoreTerminal()
{
	if (g_tiosOk)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &g_savedTios);
		g_tiosOk = false;
	}
}

static void setupRawInput()
{
	if (!isatty(STDIN_FILENO))
		return;
	if (tcgetattr(STDIN_FILENO, &g_savedTios) != 0)
		return;
	termios t = g_savedTios;
	t.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
	t.c_cc[VMIN] = 0;
	t.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) != 0)
		return;
	g_tiosOk = true;
}

static bool consoleKeyAvailable()
{
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	timeval tv{};
	return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
}

static char readConsoleChar()
{
	unsigned char c = 0;
	if (read(STDIN_FILENO, &c, 1) == 1)
		return static_cast<char>(c);
	return 0;
}

static void clearScreen()
{
	std::cout << "\033[2J\033[H" << std::flush;
}

static void sleepMs(unsigned ms)
{
	usleep(static_cast<useconds_t>(ms) * 1000);
}
#endif

bool gameOver;
const int cao = 30;
const int rong = 70;
/** Càng nhỏ rắn di chuyển càng nhanh/mượt (ms mỗi bước). */
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
		char key = 0;
#ifdef _WIN32
		if (!_kbhit())
			break;
		key = static_cast<char>(_getch());
#else
		if (!consoleKeyAvailable())
			break;
		key = readConsoleChar();
#endif

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
#ifndef _WIN32
	setupRawInput();
	atexit(restoreTerminal);
#endif
	srand((unsigned)time(0));
	cSnake snake;
	cFood food;
	randomSnake(snake);
	randomFood(food, snake);
	runGame(snake, food);
	return 0;
}
