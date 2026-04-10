#include "cSnake.h"

cSnake::cSnake(int x, int y)
{
	body.push_back({ x, y });
	huong = 0;
}

cSnake::cSnake()
{
	body.push_back({ 0, 0 });
	huong = 0;
}

void cSnake::diChuyen()
{
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
		const bool doiHuongNguoc =
			(huong == 1 && huongMoi == 2) ||
			(huong == 2 && huongMoi == 1) ||
			(huong == 3 && huongMoi == 4) ||
			(huong == 4 && huongMoi == 3);

		if (doiHuongNguoc)
			return;
	}

	this->huong = huongMoi;
}

void cSnake::datViTriDau(int x, int y)
{
	body[0].x = x;
	body[0].y = y;
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
