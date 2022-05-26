#include <iostream>
#include "Menu.h" 

//Trabalho de lab. de programação
//Feito por: Pedro Barroso AL71134

int main()
{
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	srand(time(0));
	Menu m;
	system("cls");
	m.prints();
	m.input();
	return 0;
}