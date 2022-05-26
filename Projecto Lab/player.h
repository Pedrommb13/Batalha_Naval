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
	player();	// incializaçao do player 

	char* getname(); // retorna nome do player

	int setboats();	// Função para o humano colocar os barcos

	void bot_tableset(); // Função para o bot definir os barcos

	void player_pew(); // Função para o humano disparar

	void update_prob(); //Função para atualizar a mesa de probabilidades (contem as regras do bot para jogar)

	void prt_prob(); // printa mesa de probabilidades

	int* check_prob(); //Procura pela melhor casa para jogar e retorna a casa com maior probabilidade de conter um barco

	void bot_pew();	// Função para o bot disparar

	void DEBUG(); // funçâo mutavel utilizada em debug, utilizada para procurar valores invalidos numa matriz

	int getplays(); //Retorna a quantidade de jogadas feitas no jogo

	board* getboard(); // retorna apontador da mesa
};

