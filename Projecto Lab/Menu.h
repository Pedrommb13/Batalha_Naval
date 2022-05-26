#pragma once
#include "jogo.h"
class Menu
{
private:
	jogo j;
	int arrow_pos = 5;
	int in;
	int op;
	bool debug;
public:
	void prints()
	{
		//todos os prints do Menu
		select_arrow(arrow_pos);
		play();
		options();
		gotoxy(0, 0);
	}

	void select_arrow(int y)
	{
		
		gotoxy(1, y);
		std::cout << "-->";
	}

	void play()
	{
		gotoxy(5, 5);
		std::cout << "1 - jogo humano vs computador";
		gotoxy(5, 8);
		std::cout << "2 - jogo computador vs computador";
		gotoxy(5, 11);
		std::cout << "3 - jogo humano vs humano (a seleção dos barcos é vista por ambos os jogadores)";
		gotoxy(5, 14);
		std::cout << "4 - 1000 jogo computador vs computador (apresenta no final a media de jogadas nos 1000 jogos e jogadas por jogo)";
	}

	void options()
	{
		gotoxy(5, 17);
		std::cout << "5 - debug option(desativa os prints, ativar quanto calcular os 1000 jogos bot vs bot para acelerar o processo):" << j.get_player()->getboard()->getboat(1)->get_debug();
	}

	void input()
	{
		do
		{
			in = _getch();
			std::cout << in;
			op = 1;
			switch (in)
			{
			case 72:
			case 'w':
				op = 0;
				if (arrow_pos > 5)arrow_pos = arrow_pos - 3;
				break;
			case 's':
			case 80:
				op = 0;
				if (arrow_pos < 17)arrow_pos = arrow_pos + 3;
				break;
			case 13:
				switch (arrow_pos)
				{
				case 5:
					system("cls");
					j.player_vs_bot();
					break;
				case 8:
					system("cls");
					j.bot_vs_bot();
					break;
				case 11:
					system("cls");
					j.player_vs_player();
					break;
				case 14:
					system("cls");
					bot_1000();
					break;
				case 17:
					if (j.get_player()->getboard()->getboat(1)->get_debug() == 0) j.get_player()->getboard()->getboat(1)->set_debug(1);
					else  j.get_player()->getboard()->getboat(1)->set_debug(0);
					op = 0;
					debug = j.get_player()->getboard()->getboat(1)->get_debug();
					break;
				}
				break;
			case 49:
				system("cls");
				j.player_vs_bot();
				break;
			case 50:
				system("cls");
				j.bot_vs_bot();
				break;
			case 51:
				system("cls");
				j.player_vs_player();
				break;
			case 52:
				system("cls");
				bot_1000();
			case 53:
				if (j.get_player()->getboard()->getboat(1)->get_debug() == 0) j.get_player()->getboard()->getboat(1)->set_debug(1);
				else  j.get_player()->getboard()->getboat(1)->set_debug(0);
				debug = j.get_player()->getboard()->getboat(1)->get_debug();
				op = 0;
				break;
			case 27:
				break;
			default:
				op = 0;
				break;
			}
			system("cls");
			prints();

		} while (op == 0);
	}

	void bot_1000() //função para debug !! faz 200 bot_vs_bot, printa a media de jogadas por jogo e a quantidade de vezes que o bot 1 (player p) ganha
	{
	#define t 1000
		jogo* j;
		float wins = 0;
		double plays[t];
		for (int i = 0; i < t; i++)
		{
			j = new jogo;
			j->get_player()->getboard()->getboat(1)->set_debug(debug);
			plays[i] = j->bot_vs_bot();
			if (j->winner() == 0) wins++;
			delete j;
			std::cout << i;
			gotoxy(0, 0);
		}
		for (int i = 0; i < t; i++) std::cout << plays[i] << ";";
		double n = 0;
		for (int i = 0; i < t; i++) n = n + plays[i];
		n = n / t;
		std::cout.precision(5);
		std::cout << std::endl << "media: " << n;
		std::cout << std::endl << "player wins: " << wins / (t / (t / 10)) << " %";
		_getch();
	}

};
