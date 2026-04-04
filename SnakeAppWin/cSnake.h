#pragma once
#include <vector>

typedef struct ToaDo
{
	int x;
	int y;
} TD;

class cSnake
{
private:
	std::vector<TD> body;
	int huong;
public:
	cSnake();
	cSnake(int, int);

	void diChuyen();
	void phatTrien();
	void doiHuong(int);
	void datViTriDau(int x, int y);
	TD toaDoDauRan() const;
	const std::vector<TD>& toaDoThanRan() const;
};

class cFood
{
private:
	TD toaDo;
public:
	cFood();
	cFood(int, int);
	void datViTri(int x, int y);
	TD toaDoFood() const;
};
