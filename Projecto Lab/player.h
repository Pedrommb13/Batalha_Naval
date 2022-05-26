#pragma once
#include <iostream>
#include <conio.h>
#include "board.h"
#include <time.h>
class player
{
private:
	char name[16] = "Player";
	board m;
	boat shot;
	int plays = 1;
	int id;
	float prob[10][10];
	int boat_found[12];
	int static inc;
public:
	player();	// incializa�ao do player 

	char* getname(); // retorna nome do player

	int setboats();	// Fun��o para o humano colocar os barcos

	void bot_tableset(); // Fun��o para o bot definir os barcos

	void player_pew(); // Fun��o para o humano disparar

	void update_prob(); //Fun��o para atualizar a mesa de probabilidades (contem as regras do bot para jogar)

	void prt_prob(); // printa mesa de probabilidades

	int* check_prob(); //Procura pela melhor casa para jogar e retorna a casa com maior probabilidade de conter um barco

	void bot_pew();	// Fun��o para o bot disparar

	void DEBUG(); // fun��o mutavel utilizada em debug, utilizada para procurar valores invalidos numa matriz

	int getplays(); //Retorna a quantidade de jogadas feitas no jogo

	board* getboard(); // retorna apontador da mesa
};

