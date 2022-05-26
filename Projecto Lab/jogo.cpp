#include "jogo.h"

int jogo::winner()
{
	if (get_player()->getboard()->getboat(1)->get_debug()) return p.getboard()->check_lost();
	if (p.getboard()->check_lost() == 1)
	{
		gotoxy(1, 23);
		std::cout << "bot ganhou!";
	}
	else {
		gotoxy(1, 23);
		std::cout << p.getname() << " ganhou!";
	}
	gotoxy(0, 23);
	return p.getboard()->check_lost();
}

int jogo::player_vs_bot()
{
	system("cls");
	bot.getboard()->tableshow();
	p.getboard()->tableshow();
	p.setboats();
	bot.bot_tableset();
	do
	{
		bot.player_pew();
		p.bot_pew();
	} while (p.getboard()->check_lost() != 1 && bot.getboard()->check_lost() != 1);
	
	return p.getplays();
}

int jogo::bot_vs_bot()
{
	//system("cls");
	gotoxy(0, 0);
	bot.getboard()->tableshow();
	p.getboard()->tableshow();
	p.bot_tableset();
	bot.bot_tableset();
	bool play = rand() % 2;
	do
	{
		//_getch(); //debug
		if (play) for (int k = 0; k < 3; k++)
		{
			bot.bot_pew();
			//_getch(); //debug
		}
		if (play == 0)for (int k = 0; k < 3; k++)
		{
			p.bot_pew();
			
			//_getch(); //debug
		}
		//_getch(); //debug
		play = not play;
	} while (p.getboard()->check_lost() != 1 && bot.getboard()->check_lost() != 1);
	int plays;
	if (p.getboard()->check_lost() == 1)  plays = bot.getplays();
	else{ plays = p.getplays(); }
	
	return plays;
}

int jogo::player_vs_player()
{
	system("cls");
	bot.getboard()->tableshow();
	p.getboard()->tableshow();
	p.setboats();
	bot.setboats();
	do
	{
		bot.player_pew();
		p.player_pew();
	} while (p.getboard()->check_lost() != 1 && bot.getboard()->check_lost() != 1);
	
	return p.getplays();
}