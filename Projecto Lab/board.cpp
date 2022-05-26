#include "boat.h"
#include "board.h"
#include <iomanip> 

int board::inc=0;

board::board()
{
	int i, j;
	inc++;
	t = inc;

	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			table[i][j] = -16;
		}
	}
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			table_view[i][j] = -16;
		}
	}
	for (i = 0; i < 12; i++)
	{
		boats_alive[i] = 1;
	}
	if (inc == 2)inc = 0;
};

void gotoxy(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}	// mover cursor para ponto da consola

void board::tableshow()
{
	if (getboat(1)->get_debug()) return;
	char ce = 218, be = 192, cd = 191, bd = 217, lv = 179, lh = 196, l4 = 197, l3b = 194, l3c = 193, l3d = 195, l3e = 180;
	clear();
	int i, j, x = 4, y = 2;
	x = 4;
		if (t == 2 ) { x = 74; }
		gotoxy(x, y);
		std::cout << ce;
		gotoxy(x + 40, y);
		std::cout << cd;
		gotoxy(x, y + 20);
		std::cout << be;
		gotoxy(x + 40, y + 20);
		std::cout << bd;

		for (j = 0; j < 11; j++)
		{
			for (i = 0; i < 39; i++)
			{
				gotoxy(x + 1 + i, y + (j * 2));
				std::cout << lh;
			}//desenha as linhas horizontais
			for (i = 0; i < 19; i++)
			{
				gotoxy(x + (j * 4), y + 1 + i);
				std::cout << lv;
			}//desenha as linhas verticais	
		}	

		for (j = 1; j < 10; j++)
		{
			for (i = 1; i < 10; i++)
			{
				gotoxy(x + (j * 4), y + (i * 2));			//desenha os cruzamentos de linhas interiores
				std::cout << l4;
				gotoxy(x + (i * 4), y);						//linhas superiores
				std::cout << l3b;
				gotoxy(x + (i * 4), y + 20);				//linhas inferiores
				std::cout << l3c;
				gotoxy(x + 40, y + (i * 2));				//linhas esquerda
				std::cout << l3e;
				gotoxy(x, y + (i * 2));						//linhas direita
				std::cout << l3d;
			}
		}
};

void board::printcord(int x_, int y_, char c)
{
	if (getboat(1)->get_debug()) return;
	int x = 6, y = 3;
	if (t == 2) { x = 76; }
	gotoxy(x + ((x_) * 4), y + ((y_) * 2));
	std::cout << c;
}

void board::_printcord(int x_, int y_, char c)
{
	if (getboat(1)->get_debug()) return;
	int x = 6, y = 3;
	if (t == 2) { x = 76; }
	gotoxy(x + ((x_) * 4), y + ((y_) * 2));
	std::cout << "\033[91m" << c << "\033[0m";
}

void board::_printprob(int x_, int y_, float c)
{
	if (getboat(1)->get_debug()==1) return;
	int x =5, y = 41;
	if (t == 2) { x = 64; }
	gotoxy(x + ((x_) * 5), y + ((y_) * 2));
	std::cout.precision(3);

	if (c*100 == 0)std::cout << "\033[91m" << c*100 << "\033[0m";
	else if (c * 100 < 50) std::cout << "\033[33m" << c * 100 << "\033[0m";
	else std::cout << "\033[32m" << c * 100 << "\033[0m";
	gotoxy(6, 3);
}

void board::mapboats()
{
	int j, i, k;
	int *cords,x=0;
	
	if (t == 2) { x = 70; }
	
	for (j = 0; j < 13; j++)
	{
		for (i = 0; i < 13; i++)
		{
			table[i][j] = -16;							//limpa a mesa
		}
	}

	for (k = 1; k < 12; k++)
	{
		boat* boat = this->getboat(k);
		cords = boat->getcords();
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				//printboard();
				if (boat->getset()) if (boat->getblocks(i, j) != ' ')table[cords[0] + j][cords[1] + i] = boat->getid();			//desenha novo barco na mesa
			}
		}
	}
}

void board::printboard()
{
	if (getboat(1)->get_debug()) return;
	int j, i;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printcord(i, j, table[i][j]+0x30);
		}
	}
	gotoxy(0, 23);
}

void board::printboard_view()
{
	if (getboat(1)->get_debug()) return;
	int j, i;
	
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (table_view[i][j] != -16) _printcord(i, j, table_view[i][j] + 0x30);
		}
	}
	
}

void board::printboat(boat *boat)
{
	if (getboat(1)->get_debug()) return;
	int* cords;
	cords = boat->getcords();
	int j, i;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (boat->getset()==1)if (boat->getblocks(i, j) != ' ') printcord(cords[0] + j, cords[1] + i, boat->getid() + 0x30);
			if (boat->getset()==2)if (boat->getblocks(i, j) != ' ') _printcord(cords[0] + j, cords[1] + i, boat->getid() + 0x30);
		}
	}
	
}

void board::print_all_boats()
{
	if (getboat(1)->get_debug()) return;
	int i;
	for (i=1;i<12;i++)
	{
		boat *boat =getboat(i);
		if (boat->getset() > 0) { printboat(boat); }
	}
}

void board::clear()
{
	if (getboat(1)->get_debug()) return;
	int j, i,x=0;
	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 10; i++)
		{
			printcord(i+x, j, ' ');
		}
	}	//limpa os objetos das mesas
}

int board::input(boat *boat,int k)
{
	int in = k;
	int* cords;
	int type, next=0;
	cords = boat->getcords();
	type = boat->gettype();
		switch (in)
		{
		case 'r':
			if (cords[1] < 11 - type && cords[0] < 11 - type || type==5) { boat->rotate(); }
			clear();
			mapboats();
			break;
		case 72:
		case 'w':
			boat->move('w');
			clear();
			mapboats();
			break;
		case 'a':
		case 75:
			boat->move('a');
			clear();
			mapboats();
			break;
		case 's':
		case 80:
			boat->move('s');
			clear();
			mapboats();
			break;
		case 'd':
		case 77:
			boat->move('d');
			clear();
			mapboats();
			break;
		case 13:
			next++;
			break;
		case 8:
			next--;
			break;
		case 32:
			next = 32;
			break;
		default:
			break;
		}
		//gotoxy(0, 23);
		//std::cout<< "Tecla: " << in<< "    ";
	return next;
}

boat* board::getboat(int boat_id)
{
	boat* boat;
	switch (boat_id)
	{
	case 1:
		boat = &sub_1;
		return boat;
	case 2:
		boat = &sub_2;
		return boat;
	case 3:
		boat = &sub_3;
		return boat;
	case 4:
		boat = &sub_4;
		return boat;
	case 5:
		boat = &ct_1;
		return boat;
	case 6:
		boat = &ct_2;
		return boat;
	case 7:
		boat = &ct_3;
		return boat;
	case 8:
		boat = &cr_1;
		return boat;
	case 9:
		boat = &cr_2;
		return boat;
	case 10:
		boat = &co;
		return boat;
	case 11:
		boat = &pa;
		return boat;
	default:
		boat = &sub_1;
		return boat;
	}
}

int board::getalive(int id)
{
	return boats_alive[id];
}

bool board::all_set()
{
	bool n = 1;
	int i;
	for (i = 1; i < 12; i++)
	{
		boat* boat = getboat(i);
		if (boat->getset() == 0)n = 0;
	}
	if (n == 0)
	{
		gotoxy(0, 25);
		std::cout << "Ainda nao defiiniste todos os barcos";
	}
	return n;
}

void board::clear_msg_box()
{
	int i;
	gotoxy(0, 25);
	for (i = 0; i < 35; i++)	std::cout << " ";
}

int board::check(int bot)
{
	int n[12] = { 1 };

	int i = 0, j = 0, ret = 1;

	if (bot==1)
	{
		for (i = 0; i < 12; i++)n[i] = 1;
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (table[i][j] > 0) { n[table[i][j]] = 1; }
		}
	}

	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 11; j++)
		{
			if (i < 14)if (table[i][j] != -16 && table[i + 1][j] != -16 && table[i][j] != table[i + 1][j]) { n[(table[i][j])] = 0; n[(table[i + 1][j])] = 0; }
			if (i > 0)if (table[i][j] != -16 && table[i - 1][j] != -16 && table[i][j] != table[i - 1][j]) { n[(table[i][j])] = 0; n[(table[i - 1][j])] = 0; }
			if (j < 14)if (table[i][j] != -16 && table[i][j + 1] != -16 && table[i][j] != table[i][j + 1]) { n[(table[i][j])] = 0; n[(table[i][j + 1])] = 0; }
			if (j > 0)if (table[i][j] != -16 && table[i][j - 1] != -16 && table[i][j] != table[i][j - 1]) { n[(table[i][j])] = 0; n[(table[i][j - 1])] = 0; }
		}
	}

	for (i = 10; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (table[i][j] != -16) ret = 0;
			if (table[j][i] != -16) ret = 0;
		}
	}

	for (i = 0; i < 11; i++)if (n[i] == 0) ret = 0;

	if (ret == 0 && bot==0 && (getboat(1)->get_debug()==0))
	{
		clear_msg_box();
		gotoxy(0, 25);
		std::cout << "Barcos invalidos: ";
		for (i = 0; i < 12; i++)
		{
			if (n[i] == 0)std::cout << i << " ";
		}
	}
	return ret;
}

int board::check_shot(boat shot)
{
	int i, j, n[11];
	bool ret = 1;

	for (i = 0; i < 11; i++)
	{
		n[i] = 0;
	}

	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 11; j++)
		{
			if (table[i][j] != -16 && table[i][j] != 40) n[(table[i][j])] = 1;
		}
	}


	return ret;
}

bool board::check_lost()
{
	int i, j, n[12];
	bool ret = 1;

	for (i = 0; i < 12; i++)
	{
		n[i] = 0;
	}

	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 11; j++)
		{
			if (table[i][j] != -16 && table[i][j] != 40) n[(table[i][j])] = 1;
		}
	}

	for (i = 0; i < 11; i++)
	{
		if (n[i] == 1)
		{
			ret = 0;
		}
		else
		{
			boat* boat;
			boat = getboat(i + 1);
			boat->setid(-1);
		}
	}
	return ret;
}

int board::boom(boat shot)																							//0=invalido
{																													//1=nao acertou	
	int i, j, n[12]{ 1 };																							//2=acertou
	int ret = 1;																									//3=afundou
	int* cords = shot.getcords();
	if (table[cords[0]][cords[1]] == -2 || table[cords[0]][cords[1]] == 40) ret = 0;
	if (table[cords[0]][cords[1]] > 0 && table[cords[0]][cords[1]] < 12) {
		ret = 2;
		if (getboat(1)->get_debug() == 0)
		{
			gotoxy(0, 25);
			std::cout << "Atingiste o barco " << table[cords[0]][cords[1]] << "! ";
		}
	}
	if (table[cords[0]][cords[1]] != -16 && table[cords[0]][cords[1]] != -2) { if (table[cords[0]][cords[1]] != 40) table_view[cords[0]][cords[1]] = table[cords[0]][cords[1]]; table[cords[0]][cords[1]] = 40; }
	else { table[cords[0]][cords[1]] = -2; table_view[cords[0]][cords[1]] = -2; }
	if (ret == 2)
	{
		for (i = 0; i < 11; i++)
		{
			for (j = 0; j < 11; j++)
			{
				//printboard(); //debug
				if (table[i][j] != -16 && table[i][j] != 40) n[(table[i][j])] = 1;
			}
		}
		for (i = 1; i < 12; i++)
		{
			if (n[i] == 0 && boats_alive[i] == 1)
			{
				if (getboat(1)->get_debug()==0) std::cout << "O barco " << i << " afogou!";
				ret = 3;
			}
		}
		for (i = 0; i < 12; i++)
		{
			boats_alive[i] = n[i];
		}
	}
	return ret;
}

int board::getview(int i, int j)
{
	return table_view[i][j];
}

int board::gettable(int i, int j)
{
	return table[i][j];
}