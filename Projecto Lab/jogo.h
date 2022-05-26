#pragma once
#include "player.h" 
class jogo
{
private:
	player p;
	player bot;
public:

	int bot_vs_bot();				//jogo bot contra bot

	int player_vs_bot();			//jogo humano contra bot

	int player_vs_player();			//jogo humano contra humano ; Por terminar!

	int winner();

	player* get_player() {
		return &p;
	}
};

