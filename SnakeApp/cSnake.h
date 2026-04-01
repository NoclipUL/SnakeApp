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
	cSnake(int, int);

	void diChuyen();
	void phatTrien();
	void doiHuong(int);
	TD toaDoDauRan() const;
	const std::vector<TD>& toaDoThanRan() const;
	
};

