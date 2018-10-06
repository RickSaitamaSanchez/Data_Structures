#include <stdio.h>
#include <iostream>
#include "interface.h"
#include "intSLList.cpp"
#include "intDLList.cpp"
#include "intCLList.h"
#include "intStack.h"
#include "intQueue.h"

using namespace std;

void clearScreen() {
	printf("\33[H\33[2J");
}

void pressEnter() {
	cout << "Pressione enter para continuar...";
	char temp = 'x';
	cin.ignore(); // buffer of option choose
	cin.ignore(); // actual getting enter
}

void printHeader() {
	cout << " -------------------  Trabalho Acadêmico  -------------------- " << endl;
	cout << "|            Universidade Estadual do Ceará (UECE)            |" << endl;
	cout << "|Disciplina: Estrutura de Dados I                             |" << endl;
	cout << "|Docente: Bruno Araujo Lima.                                  |" << endl;
	cout << "|Discente: Gabriel Furtado Lins Melo.                         |" << endl;
	cout << "|Matrícula: 1394225                                           |" << endl;
	cout << " ------------------------------------------------------------- " << endl << endl;
}

void mainMenu() {
	bool leave = false;
	while(!leave) {
		clearScreen();
		printHeader();
		cout << "1. Lista encadeada simples.\n";
		cout << "2. Lista duplamente encadeada.\n";
		cout << "3. Lista circular.\n";
		cout << "4. Fila.\n";
		cout << "5. Pilha.\n";
		cout << "6. Sair.\n\n";

		int op;
		cout << "Opção: ";
		cin >> op;
		switch(op) {
			case 1:
				menuSLL();
				break;
			case 2:
				menuDLL();
				break;
			case 3:
				menuCLL();
				break;		
			case 4:
				menuQueue();
				break;
			case 5:
				menuStack();
				break;
			case 6:
				leave = true;
				clearScreen();
				break;
			default:
				cout << "Opção não reconhecida.\n";
				pressEnter();
				break;
		}
	}
}