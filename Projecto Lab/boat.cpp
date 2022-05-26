#include "boat.h"
int boat::inc = 0;
bool boat::debug = 0;
boat::boat()
{
	int i, j;
	type = 1;
	set = 2;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			blocks[i][j] = ' ';
		}
	}
	blocks[0][0] = 'X';
}

boat::boat(int t)
{
	inc++;
	if (inc == 0) { inc = 1; }id = inc;
	type = t;
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			blocks[i][j] = ' ';
		}
	}
	if (t < 5) for (i = 0; i < t; i++)
	{
		blocks[i][0] = 'O';
	}
	if (t == 5)
	{
		for (i = 0; i < 3; i++)
		{
			blocks[i][0] = 'O';
			blocks[1][i] = 'O';
		}
	}
}

void boat::setid(int i)
{
	inc = i;
}

char boat::getblocks(int x, int y)
{
	return blocks[x][y];
}

int* boat::getcords()
{
	return cords;
}

int boat::gettype()
{
	return type;
}

void boat::rotate()
{
	int i, j, x = cords[0], y = cords[1], o = orientacion;
	if (type < 5)
	{
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				blocks[j][i] = ' ';
			}
		}
		if (orientacion == 0)
		{
			for (i = 0; i < type; i++)
			{
				blocks[0][i] = 'O';
				orientacion = 1;
			}
			return;
		}
		else if (orientacion == 1)
		{
			for (i = 0; i < type; i++)
			{
				blocks[i][0] = 'O';
				orientacion = 0;

			}
			return;
		}
	}
	else
	{
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				blocks[j][i] = ' ';
			}
		}
		if (orientacion == 0)
		{
			for (i = 0; i < 3; i++)
			{
				blocks[i][1] = 'O';
				blocks[0][i] = 'O';
				orientacion = 1;
			}
			return;
		}
		else if (orientacion == 1)
		{
			for (i = 0; i < 3; i++)
			{
				blocks[1][i] = 'O';
				blocks[i][2] = 'O';
				orientacion = 2;
			}
			return;
		}
		else if (orientacion == 2)
		{
			for (i = 0; i < 3; i++)
			{
				blocks[i][1] = 'O';
				blocks[2][i] = 'O';
				orientacion = 3;
			}
			return;
		}
		else if (orientacion == 3)
		{
			for (i = 0; i < 3; i++)
			{
				blocks[i][0] = 'O';
				blocks[1][i] = 'O';
				orientacion = 0;
			}
			return;
		}
	}
}

void boat::move(char in)
{
	int op_orientacion = orientacion;
	int t = type;
	switch (in)
	{
	default:
		break;
	case 's':
		if (type == 5)
		{
			if (cords[1] < 7) { cords[1] = cords[1] + 1; }
			break;
		}
		if (op_orientacion == 1) { op_orientacion = 0; }
		else { op_orientacion = 1; }
		if (cords[1] < 10 - (t * op_orientacion) - (1 * orientacion)) { cords[1] = cords[1] + 1; }
		break;
	case 'w':
		if (cords[1] > 0) { cords[1] = cords[1] - 1; }
		break;
	case 'a':
		if (cords[0] > 0) { cords[0] = cords[0] - 1; }
		break;
	case 'd':
		if (type == 5)
		{
			if (cords[0] < 7) { cords[0] = cords[0] + 1; }
			break;
		}
		if (op_orientacion == 1) { op_orientacion = 0; }
		else { op_orientacion = 1; }
		if (cords[0] < 10 - (t * orientacion) - (1 * op_orientacion)) { cords[0] = cords[0] + 1; }
		break;
	}
}

void boat::setpos(int x, int y, int ori)
{
	cords[0] = x;
	cords[1] = y;
	orientacion = ori;
}

int boat::getid()
{
	return id;
}

int boat::gettable()
{
	return table_id;
}

void boat::setset(int i)
{
	set = i;
}

int boat::getset()
{
	return this->set;
}