#include "player.h"
int player::inc = 0;

player::player()
{
	id = inc++;
	for (int i = 0; i < 12; i++)
	{
		boat_found[i] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		
		for (int j = 0; j < 10; j++)
		{
			prob[i][j] = 0.25;
		}
	}
	update_prob();
	//_getch();
	getboard()->getboat(1)->setid(0);
	if (inc == 2) inc = 0;
}

char* player::getname()
{
	return name;
}

int player::setboats()
{
	board* board = getboard();

	if (board->getboat(1)->get_debug() == 0)
	{
		gotoxy(75, 23);
		std::cout << "W,A,S,D / setas --> mover";
		gotoxy(75, 24);
		std::cout << "R --> rodar";
		gotoxy(75, 25);
		std::cout << "ENTER --> proximo barco";
		gotoxy(75, 26);
		std::cout << "backspace (apagar) --> barco anterior";
		gotoxy(75, 27);
		std::cout << "espaco --> confirmar tudo";
	}
	int in = 0, out = 0, _set = 0, boat_id = 1;
	
	boat* boat;
	do
	{
		do
		{
			
			if (out == 1 && boat_id < 11) boat_id++;
			if (out == -1 && boat_id > 1) boat_id--;
			boat = board->getboat(boat_id);
			
			if (board->getboat(1)->get_debug() == 0){
				gotoxy(0, 24);
				std::cout << "barco: " << boat_id << " ";
			}
			boat->setset(2);
			board->print_all_boats();
			do
			{
				in = _getch();
				out = board->input(boat, in);
				board->print_all_boats();
			} while (out == 0);
			if (out == 32) { _set = board->all_set(); }
			boat->setset(1);
		} while (in != 32 || _set != 1);
		m.mapboats();
		m.printboard();
	} while (m.check(0) != 1);
	if (board->getboat(1)->get_debug() == 0)for (int i = 23; i < 28;i++)
	{
		for (int j = 0; j < 120; j++) std::cout << " ";
	}
	return in;
}

void player::bot_tableset()
{
	int boat_id;
	do
	{
		for (boat_id = 1; boat_id < 12;)
		{
			boat* boat = m.getboat(boat_id);
			int* cords = boat->getcords();
			int type = boat->gettype();
			int ori=0;
			if (type == 5) { ori = rand() % 4; }
			else { ori = rand() % 2; }
			boat->setpos(rand() % 10, rand() % 10, ori);
			if (cords[1] < 11 - type && cords[0] < 11 - type) boat->rotate();
			boat->setset(1);
			m.mapboats();
			//m.printboard();
			if (m.check(1))boat_id++;
		}
	} while (m.check(2) != 1);
	//m.printboard();
}

void player::player_pew()
{
	if (getboard()->getboat(1)->get_debug() == 0) {
		gotoxy(75, 23);
		std::cout << "W,A,S,D / setas --> Mover";
		gotoxy(75, 24);
		std::cout << "ENTER --> Disparar";
	}
	
	int done = 0, ret;
	do
	{
		m.printboat(&shot);
		do
		{
			m.clear();
			m.printboard_view();
			m.printboat(&shot);
			done = 0;
			switch (_getch())
			{
			case 72:
			case 'w':
				shot.move('w');
				//m.clear();
				//m.printboard();
				m.printboard_view();
				m.printboat(&shot);
				break;
			case 'a':
			case 75:
				shot.move('a');
				//m.clear();
				//m.printboard();
				m.printboard_view();
				m.printboat(&shot);
				break;
			case 's':
			case 80:
				shot.move('s');
				//m.clear();
				//m.printboard();
				m.printboard_view();
				m.printboat(&shot);
				break;
			case 'd':
			case 77:
				shot.move('d');
				//m.clear();
				//m.printboard();
				m.printboard_view();
				m.printboat(&shot);
				break;
			case 13:
			case 32:
				done = 1;
				m.printboard_view();
				break;
			}
		} while (done != 1);
		ret = m.boom(shot);
		_getch();
		if (getboard()->getboat(1)->get_debug() == 0) {
			gotoxy(0, 25);
			std::cout << "                                        ";
		}
	} while (ret == 0);
}

void player::update_prob()
{
	float a = 25, b = 0;
	int i, j;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (prob[i][j] != 0 ) { b++; }
			if (m.getview(i, j) < 12 && m.getview(i, j) > 0) { a--; }
		}
	}
	
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (m.getview(i, j) > 0 && m.getview(i, j) < 12)boat_found[m.getview(i, j)] = 1;
		}
	}

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (prob[i][j] == 0) {}
			else if (m.getview(i, j) != -16)
			{
				prob[i][j] = 0;
			}
			else if (prob[i][j] < 0.75) { prob[i][j] = a / b; }						// a->blocos de barco por encontrar
																					// b->casas possiveis 
			/*if (prob[i][j] && plays < 25)
			{
				float x = i - 4.5;
				float y = j - 4.5;
				x = fabs(x);
				y = fabs(y);
				prob[i][j] = prob[i][j] + (0.1 / x) + (0.1 / y);
			}*/

			

			if (m.getview(i, j) < 12 && m.getview(i, j) > 0 && m.getalive(m.getview(i, j)) == 0)
			{
				if (i < 9)prob[i + 1][j] = 0;
				if (i > 0)prob[i - 1][j] = 0;
				if (j < 9)prob[i][j + 1] = 0;
				if (j > 0)prob[i][j - 1] = 0;
			}
			else if (m.getview(i, j) < 12 && m.getview(i, j) > 0 && m.getalive(m.getview(i, j)) == 1)
			{
				if (i < 9 && prob[i + 1][j])prob[i + 1][j] = 0.8;
				if (i > 0 && prob[i - 1][j])prob[i - 1][j] = 0.8;
				if (j < 9 && prob[i][j + 1])prob[i][j + 1] = 0.8;
				if (j > 0 && prob[i][j - 1])prob[i][j - 1] = 0.8;
				if (m.getview(i, j) < 11 && m.getview(i, j) > 0)
				{
					if (i > 0 && m.getview(i, j) == m.getview(i - 1, j))
					{
						if (i > 1 && prob[i - 2][j])prob[i - 2][j] = 0.9;
						if (i < 9 && prob[i + 1][j])prob[i + 1][j] = 0.9;

						if (j < 9 && prob[i][j + 1])prob[i][j + 1] = 0;
						if (j > 0 && prob[i][j - 1])prob[i][j - 1] = 0;
					}
					if (i > 0 && m.getview(i, j) == m.getview(i + 1, j))
					{
						if (i < 8 && prob[i + 2][j])prob[i + 2][j] = 0.9;
						if (i > 0 && prob[i - 1][j])prob[i - 1][j] = 0.9;

						if (j < 9 && prob[i][j + 1])prob[i][j + 1] = 0;
						if (j > 0 && prob[i][j - 1])prob[i][j - 1] = 0;
					}
					if (i > 0 && m.getview(i, j) == m.getview(i, j - 1))
					{
						if (i > 1 && prob[i][j - 2])prob[i][j - 2] = 0.9;
						if (i < 9 && prob[i][j + 1])prob[i][j + 1] = 0.9;

						if (i > 0 && prob[i - 1][j])prob[i - 1][j] = 0;
						if (i < 9 && prob[i + 1][j])prob[i + 1][j] = 0;
					}
					if (i > 0 && m.getview(i, j) == m.getview(i, j + 1))
					{
						if (i < 8 && prob[i][j + 2])prob[i][j + 2] = 0.9;
						if (i > 0 && prob[i][j - 1])prob[i][j - 1] = 0.9;

						if (i > 0 && prob[i - 1][j])prob[i - 1][j] = 0;
						if (i < 9 && prob[i + 1][j])prob[i + 1][j] = 0;
					}
				}
			}
		}
	}
	
	if (m.getalive(11) == 1)
	{
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (m.getview(i, j) == 11)
				{
					if (i < 9)if (m.getview(i, j) == m.getview(i + 1, j) && m.getalive(m.getview(i, j)) == 1)
					{
						if (i < 8 && prob[i + 2][j])prob[i + 2][j] = 0.9;
						if (i > 0 && prob[i - 1][j])prob[i - 1][j] = 0.9;
					}
					else if (j < 9)if (m.getview(i, j) == m.getview(i, j + 1) && m.getalive(m.getview(i, j)) == 1)
					{
						if (j < 8 && prob[i][j + 2])prob[i][j + 2] = 0.9;
						if (j > 0 && prob[i][j - 1])prob[i][j - 1] = 0.9;
					}
				}
			}
		}
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (m.getview(i, j) == 11)
				{
					if (m.getview(i, j) == m.getview(i + 1, j) && m.getview(i, j) == m.getview(i + 2, j))
					{
						if (i < 7)prob[i + 3][j] = 0;
						if (i > 0)prob[i - 1][j] = 0;

						if (j > 0) if (m.getview(i, j + 1) == -2)prob[i][j - 1] = 0;
						if (j < 9) if (m.getview(i, j - 1) == -2)prob[i][j + 1] = 0;
						if (j > 0 && i < 8) if (m.getview(i + 2, j + 1) == -2)prob[i + 2][j - 1] = 0;
						if (j < 9 && i < 8) if (m.getview(i + 2, j - 1) == -2)prob[i + 2][j + 1] = 0;

						if (i < 9 && j > 1) if (m.getview(i + 1, j - 2) > -3 && m.getview(i + 1, j - 2) < 11) prob[i + 1][j - 1] = 0;
						if (i < 9 && j < 9) if (m.getview(i + 1, j + 2) > -3 && m.getview(i + 1, j + 2) < 11) prob[i + 1][j + 1] = 0;

						if (j == 9 && prob[i + 1][j - 2] && prob[i + 1][j - 1]) { prob[i + 1][j - 1] = 0.9; prob[i + 1][j - 2] = 0.9; }
						if (j == 0 && prob[i + 1][j + 2] && prob[i + 1][j + 1]) { prob[i + 1][j + 1] = 0.9; prob[i + 1][j + 2] = 0.9; }

						if (j < 9)if (m.getview(i, j) == m.getview(i, j - 1) && prob[i][j + 1]) prob[i][j + 1] = 0.9;
						if (j > 0)if (m.getview(i, j) == m.getview(i, j + 1) && prob[i][j - 1]) prob[i][j - 1] = 0.9;
						if (j < 9 && i < 8)if (m.getview(i, j) == m.getview(i + 2, j - 1) && prob[i + 2][j + 1]) prob[i + 2][j + 1] = 0.9;
						if (j > 0 && i < 8)if (m.getview(i, j) == m.getview(i + 2, j + 1) && prob[i + 2][j - 1]) prob[i + 2][j - 1] = 0.9;
						if (j > 1 && i < 9)if (m.getview(i, j) == m.getview(i + 1, j - 1) && prob[i + 1][j - 2]) prob[i + 1][j - 2] = 0.9;
						if (j < 8 && i < 9)if (m.getview(i, j) == m.getview(i + 1, j + 1) && prob[i + 1][j + 2]) prob[i + 1][j + 2] = 0.9;
					}
					if (m.getview(i, j) == m.getview(i, j + 1) && m.getview(i, j) == m.getview(i, j + 2))
					{
						if (j < 7)prob[i][j + 3] = 0;
						if (j > 0)prob[i][j - 1] = 0;

						if (i > 0) if (m.getview(i + 1, j) == -2)prob[i - 1][j] = 0;
						if (i < 9) if (m.getview(i - 1, j) == -2)prob[i + 1][j] = 0;
						if (i > 0 && j < 8) if (m.getview(i + 1, j + 2) == -2)prob[i - 1][j + 2] = 0;
						if (i < 9 && j < 8) if (m.getview(i - 1, j + 2) == -2)prob[i + 1][j + 2] = 0;

						if (i > 1 && j < 9) if (m.getview(i - 2, j + 1) > -3 && m.getview(i - 2, j + 1) < 11) prob[i - 1][j + 1] = 0;
						if (i < 9 && j < 9) if (m.getview(i + 2, j + 1) > -3 && m.getview(i + 2, j + 1) < 11) prob[i + 1][j + 1] = 0;

						if (i == 9 && prob[i - 2][j + 1] && prob[i - 1][j + 1]) { prob[i - 1][j + 1] = 0.9; prob[i - 2][j + 1] = 0.9; }
						if (i == 0 && prob[i + 2][j + 1] && prob[i + 1][j + 1]) { prob[i + 1][j + 1] = 0.9; prob[i + 2][j + 1] = 0.9; }

						if (i < 9)if (m.getview(i, j) == m.getview(i - 1, j) && prob[i + 1][j]) prob[i + 1][j] = 0.9;
						if (i > 0)if (m.getview(i, j) == m.getview(i + 1, j) && prob[i - 1][j]) prob[i - 1][j] = 0.9;
						if (j < 8 && i < 9)if (m.getview(i, j) == m.getview(i - 1, j + 2) && prob[i + 1][j + 2]) prob[i + 1][j + 2] = 0.9;
						if (i > 0 && j < 8)if (m.getview(i, j) == m.getview(i + 1, j + 2) && prob[i - 1][j + 2]) prob[i - 1][j + 2] = 0.9;
						if (i > 1 && j < 9)if (m.getview(i, j) == m.getview(i - 1, j + 1) && prob[i - 2][j + 1]) prob[i - 2][j + 1] = 0.9;
						if (j < 8 && i < 9)if (m.getview(i, j) == m.getview(i + 1, j + 1) && prob[i + 2][j + 1]) prob[i + 2][j + 1] = 0.9;
					}
					if (m.getview(i, j) == m.getview(i, j + 2))
					{
						if (j < 8 && prob[i][j + 1])prob[i][j + 1] = 0.9;
					}
					if (m.getview(i, j) == m.getview(i + 2, j))
					{
						if (i < 9 && prob[i + 1][j])prob[i + 1][j] = 0.9;
					}
				}
			}
		}
	}

	if (m.getalive(11) && boat_found[11] == 0)
	{
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (m.getview(i + 1, j) < 1 && m.getview(i - 1, j) < 1 || m.getview(i, j - 1) < 1 || m.getview(i, j + 1) < 1)
				{
					int _x = 1;
					int _y = 1;
					int x_ = 1;
					int y_ = 1;

					if ((i + 3) > 9) { _x = 0; }
					if ((j + 3) > 9) { _y = 0; }
					if ((i - 3) < 0) { x_ = 0; }
					if ((j - 3) < 0) { y_ = 0; }

					if (_x && _y)
					{
						for (int p = 3; p >= 0; --p)
						{
							for (int _p = 3; _p >= 0; --_p)
							{
								if (prob[i + p][j + _p] == 0)
								{
									_x = 0;
									_y = 0;
								}
							}
						}
					}

					if (x_ && y_)
					{
						for (int p = 3; p >= 0; --p)
						{
							for (int _p = 3; _p >= 0; --_p)
							{
								if (prob[i - p][j - _p] == 0)
								{
									x_ = 0;
									y_ = 0;
								}
							}
						}
					}

					if (_x && _y)
					{
						for (int p = 3; p >= 0; --p)
						{
							for (int _p = 3; _p >= 0; --_p)
							{
								prob[i + p][j + _p] = prob[i + p][j + _p] + 0.001;
							}
						}
					}
					if (x_ && y_)
					{
						for (int p = 3; p >= 0; --p)
						{
							for (int _p = 3; _p >= 0; --_p)
							{
								prob[i - p][j - _p] = prob[i - p][j - _p] + 0.001;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (m.getview(i + 1, j) < 1 && m.getview(i - 1, j) < 1 || m.getview(i, j - 1) < 1 || m.getview(i, j + 1) < 1)
			{
				for (int q = 5; q < 11; q++)
				{
					int type = 0;
					if (m.getalive(q) && boat_found[q] == 0)
					{
						type = m.getboat(q)->gettype();

						int _x = 1;
						int _y = 1;
						if ((i + type) > 10) { _x = 0; }
						if ((j + type) > 10) { _y = 0; }
						if (_x)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i + p][j] == 0)_x = 0;
							}
						}
						if (_y)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i][j + p] == 0)_y = 0;
							}
						}
						if (_x)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i + p][j]) prob[i + p][j] = prob[i + p][j] + 0.001;
							}
						}
						if (_y)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i][j + p]) prob[i][j + p] = prob[i][j + p] + 0.001;
							}
						}
						int x_ = 1;
						int y_ = 1;
						if ((i - type) < -1) { x_ = 0; }
						if ((j - type) < -1) { y_ = 0; }
						if (x_)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i - p][j] == 0)x_ = 0;
							}
						}
						if (y_)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i][j - p] == 0)y_ = 0;
							}
						}
						if (x_)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i - p][j]) prob[i - p][j] = prob[i - p][j] + 0.001;
							}
						}
						if (y_)
						{
							for (int p = 0; p < type; p++)
							{
								if (prob[i][j - p]) prob[i][j - p] = prob[i][j - p] + 0.001;
							}
						}
					}
				}
			}
		}
	}
	if (getboard()->getboat(1)->get_debug() == 0)prt_prob();
}

void player::prt_prob()
{
	int a, b=0;
	for (int i = 0; i < 10; i++)
	{
		gotoxy(b, i * 2 + 41);
		for (a = 0; a < 117; a++)std::cout << " ";				//Print mesa de probabilidades
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m._printprob(i, j, prob[i][j]);
		}
	}
}

int* player::check_prob()
{
	//m.printboard();  //debug
	int i, j, inc = 0, best[2] = { 1,1 };
	int list[100][2];
	for (int p = 0; p < 100; p++) { list[p][0] = -1; list[p][1] = -1; }
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (prob[i][j] > prob[(best[0])][(best[1])])
			{
				best[0] = i; best[1] = j;
				for (int p = 0; p < 100; p++) { list[p][0] = -1; list[p][1] = -1; }
				inc = 0;
				list[inc][0] = best[0];
				list[inc][1] = best[1];
				inc++;
			}
			else if (prob[i][j] == prob[(best[0])][(best[1])])
			{
				best[0] = i; best[1] = j;
				list[inc][0] = best[0];
				list[inc][1] = best[1];
				inc++;
			}
		}
	}
	do
	{
		inc = rand() % inc;
		best[0] = list[inc][0];
		best[1] = list[inc][1];
	} while (prob[(best[0])][(best[1])] == 0);

	return best;
}

void player::bot_pew()
{
	//DEBUG();
	//_getch(); //DEBUG
	int check = 0;
	for (int k = 1; k < 12; k++) {
		if (m.getalive(k)) check = 1;
	}
	if (check == 0) return;
	int* best;
	best = check_prob();
	shot.setpos(best[0], best[1], 0);
	if (m.boom(shot) == 0) { gotoxy(0, 0); system("pause"); std::cout << "ERRO!ERRO!ERRO!ERRO!ERRO!"; }
	//m.printboard();//DEBUG
	update_prob();
	if (getboard()->getboat(1)->get_debug() == 0) {
		m.printboard_view();
		gotoxy(0, 0);
		std::cout << "play: " << plays++ << "                                                                                                            ";
		gotoxy(0, 25);
		std::cout << "                                                           ";
	}
	if (getboard()->getboat(1)->get_debug())plays++;
	//m.printboat(&shot);//DEBUG
}

board* player::getboard()
{
	board* board;
	board = &m;
	return board;
}

void player::DEBUG()
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{

			if (m.gettable(i, j) == 0) { gotoxy(15, 0); system("pause"); }
		}
	}
}

int player::getplays()
{
	return plays;
}