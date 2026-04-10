#include "cSnake.h"

cSnake::cSnake(int x, int y)
{
	body.push_back({ x, y });
	body.push_back({ x - 1, y });
	body.push_back({ x - 2, y });
	huong = 0;
}

cSnake::cSnake()
{
	body.push_back({ 2, 0 });
	body.push_back({ 1, 0 });
	body.push_back({ 0, 0 });
	huong = 0;
}

void cSnake::diChuyen()
{
	if (huong == 0)
		return;

	TD dauRan = body[0];

	switch (huong)
	{
	case 1:
		dauRan.x--;
		break;
	case 2:
		dauRan.x++;
		break;
	case 3:
		dauRan.y--;
		break;
	case 4:
		dauRan.y++;
		break;
	}

	body.insert(body.begin(), dauRan);
	body.pop_back();
}

void cSnake::phatTrien()
{
	body.push_back(body.back());
}

void cSnake::doiHuong(int huongMoi)
{
	if ((huong == 1 && huongMoi == 2) || (huong == 2 && huongMoi == 1) ||
		(huong == 3 && huongMoi == 4) || (huong == 4 && huongMoi == 3))
		return;

	this->huong = huongMoi;
}

void cSnake::datViTriDau(int x, int y)
{
	body.clear();
	body.push_back({ x, y });
	body.push_back({ x - 1, y });
	body.push_back({ x - 2, y });
}

TD cSnake::toaDoDauRan() const
{
	return body[0];
}

const std::vector<TD>& cSnake::toaDoThanRan() const
{
	return body;
}

cFood::cFood()
{
	toaDo.x = 0;
	toaDo.y = 0;
}

cFood::cFood(int x, int y)
{
	toaDo.x = x;
	toaDo.y = y;
}

void cFood::datViTri(int x, int y)
{
	toaDo.x = x;
	toaDo.y = y;
}

TD cFood::toaDoFood() const
{
	return toaDo;
}
