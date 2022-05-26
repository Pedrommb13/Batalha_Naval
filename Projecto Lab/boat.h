#pragma once
#include <iostream>

class boat
{
private:
	char blocks[4][4]{};		//todos os barcos encontra-se numa grelha 4x4
	int type=0;					//todos os barcos tem um tipo que é igual à sua quantidade de blocos(tipo 1,2,3,4 ou 5)

	int orientacion = 0;
	int cords[2] = { 0,0 };
	int table_id = 1; // DEBUG
	int id=0;
	static int inc;
	static bool debug;
	int set=0;
	
public:

	boat(); // inicializaçao de barco sem parametos (barco 1x1)

	boat(int t); // inicialização de barco com parametro t (t=type)

	void setid(int i); // define o ID de um barco

	char getblocks(int x, int y); // retorna um bloco da grelha do barco

	int* getcords(); // retorna os as cordenadas do barco (array[2]={x,y})

	int gettype(); //retorna o tipo do barco

	void rotate(); // roda o barco

	void move(char in); // move o barco

	void setpos(int x, int y, int ori); // define as cordenadas de um barco

	int getid(); // retorna o id do barco

	int gettable();  //retorna o table_id DEBUG
	 
	void setset(int i); // define a variavel set (0-> barco nao colocado na mesa/ 1->barco colocado na mesa)

	int getset(); // retorna a variavel set

	bool get_debug() {
		return debug;
	}

	void set_debug(bool n) {
		debug = n;
	}

	~boat() {};
};
