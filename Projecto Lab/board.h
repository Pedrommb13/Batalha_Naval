#pragma once
#include "conio.h"
#include <iostream>
#include "boat.h"
#include "Windows.h"
#include <vector>

void gotoxy(int x, int y);

class board
{
private:
	int table[13][13];
	int t = 0;
	boat sub_1{ 1 }, sub_2{ 1 }, sub_3{ 1 }, sub_4{ 1 }, ct_1{ 2 }, ct_2{ 2 }, ct_3{ 2 }, cr_1{ 3 }, cr_2{ 3 }, co{ 4 }, pa{ 5 };
	static int inc;
	int table_view[13][13];
	int boats_alive[12];
public:

	board();	// inicialização da board

	void tableshow();	// Desenha a grelha da mesa

	void printcord(int x_, int y_, char c);	// Desenha uma variavel c nas cordenadas x,y da mesa (dependendo do player que usar a função desenha na mesa relativa ao player)

	void mapboats(); // mapeia os barcos (como objeto) para o array da table 
	
	void clear(); //limpa as mesas

	int input(boat *boat,int k); //recebe os inputs do player e chama as funções relativas a cada input
	
	void printboard(); // desenha o array da mesa (e barcos caso estejam alguns mapeados no array)

	void printboat(boat *boat); // printa um barco na mesa

	boat* getboat(int boat_id); // printa todos os barcos na mesa
	
	int getalive(int id); // Returna se o barco id(id do barco) está afundado ou não

	void print_all_boats();	// Printa todos os barcos (Como objetos independentes)
	
	bool all_set();	// verifica se todos os barcos estão colocados na mesa

	void clear_msg_box(); // limpa a linhas 25 da consola

	int check(int bot); // verifica se todos os barcos tem posições legais

	int check_shot(boat shot); // DEBUG

	void printboard_view(); // Printa a info que cada jogador tem da mesa do opnente(quadrados disparados) 

	bool check_lost(); // Verifica se o jogador perdeu

	int boom(boat shot); // Coloca o Tiro de um jogador (bot ou humano) na board 

	void _printcord(int x_, int y_, char c); // Desenha uma variavel c nas cordenadas x,y da mesa, a vermelho para simbolizar pontos disparados (dependendo do player que usar a função desenha na mesa relativa ao player)

	void _printprob(int x_, int y_, float c); // Desenha uma variavel (float) da mesa de probabilidade 

	int getview(int i, int j); // retorna uma cordenada da mesa de informações do player

	int gettable(int i, int j); // retorna uma cordenada da mesa

	~board() {};
	
};


