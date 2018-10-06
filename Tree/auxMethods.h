#include <iostream>
#include <stdio.h>

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