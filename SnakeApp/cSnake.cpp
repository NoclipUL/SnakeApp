#include "cSnake.h"

static void khoiTaoThanRan(std::vector<TD>& body, int x, int y, int& huong)
{
	body.clear();

	if (x >= 2)
	{
		body.push_back({ x, y });
		body.push_back({ x - 1, y });
		body.push_back({ x - 2, y });
	}
	else
	{
		body.push_back({ x, y });
		body.push_back({ x + 1, y });
		body.push_back({ x + 2, y });
	}

	huong = 0;
}

cSnake::cSnake(int x, int y)
{
	khoiTaoThanRan(body, x, y, huong);
}

cSnake::cSnake()
{
	khoiTaoThanRan(body, 2, 0, huong);
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
	if (body.size() > 1)
	{
		TD dauMoi = body[0];

		switch (huongMoi)
		{
		case 1:
			dauMoi.x--;
			break;
		case 2:
			dauMoi.x++;
			break;
		case 3:
			dauMoi.y--;
			break;
		case 4:
			dauMoi.y++;
			break;
		default:
			return;
		}

		if (dauMoi.x == body[1].x && dauMoi.y == body[1].y)
			return;
	}

	this->huong = huongMoi;
}

void cSnake::datViTriDau(int x, int y)
{
	khoiTaoThanRan(body, x, y, huong);
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
