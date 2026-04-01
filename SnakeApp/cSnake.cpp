#include "cSnake.h"

cSnake::cSnake(int x, int y)
{
	body.push_back({ x, y });
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
	this->huong = huongMoi;
}

TD cSnake::toaDoDauRan() const
{
	return body[0];
}

const std::vector<TD>& cSnake::toaDoThanRan() const
{
	return body;
}
