#ifndef STACK
#define STACK

// #include <iostream>
// #include <stdio.h>
#include "interface.h"
#include "intSLList.h"

using namespace std;

class Stack {
public:
	Stack() {}
	~Stack() { while(!isEmpty()) pop(); } // O mesmo que usar pop() até a pilha estar vazia
	bool isEmpty() { return storage.isEmpty(); } 
	void push(int el) { storage.addToTail(el); } // Coloca no topo da pilha
	int pop(); // remove do topo e retorna o elemento removido
	int top() { return storage.getTail(); } // retorna o elemento do topo
	int size();
	int pegarPosicao(int);
	void clear() { while(!isEmpty()) pop(); } // limpa a pilha (o mesmo que o destrutor)
	void printStack() {	storage.printList(); } // imprime a pilha
private:
	IntSLList storage; // o armazenamento da pilha é dado por uma lista singularmente encadeada.
};

int Stack::pop() {
	int x = storage.getTail();
	storage.deleteFromTail(); 
	return x;	
}

int Stack::size() {
	int size = 0; // variável que vai receber o tamanho da pilha
	Stack aux; // Cria uma pilha auxiliar
	for(; !isEmpty(); aux.push(pop()), size++); // Coloca todos os elementos na auxiliar enquanto incrementa 'size';
	while(!aux.isEmpty())
		push(aux.pop()); // Coloca os elementos de volta na pilha original
	return size;
} // obs: o destrutor de aux é chamado assim que o método termina.

bool buscarElemento(int elem, Stack &s) { // Essa função não foi feita como método arbitrariamente. No entanto, 
	Stack aux;  						 // caso fosse feito como método, a lógica usada seria a mesma do método acima.
	bool flag;
	while(!s.isEmpty() && (s.top() != elem)) // procura o elemento em s até este ficar vazio
		aux.push(s.pop());
	if(s.isEmpty()) // se s chegou no final quer dizer que não encontrou o elemento
		flag = 0;
	else flag = 1;
	while(!aux.isEmpty())  
		s.push(aux.pop()); // coloca os elementos de volta em s.
	return flag;
}

int Stack::pegarPosicao(int pos) { // Essa função pega o valor de determinada posição. Onde o topo (ou a cauda) é o primeiro.
	Stack aux;
	for(int i = 1; i != pos; i++, aux.push(pop())); // Vai colocando os elementos em aux até chegar na posição desejada.
	int x = top(); // Quando i chegar em pos, o elemento do topo da lista é o desejado.
	while(!aux.isEmpty())
		push(aux.pop()); // coloca os elementos de volta na pilha original
	return x;
}

void menuStack() {
	Stack pilha;
	bool leave = false;
	while(!leave) {
		clearScreen();
		printHeader();
		cout << " --------------------------> PILHA <-------------------------- \n";
		cout << " "; pilha.printStack();
		cout << " ------------------------------------------------------------- \n";
		cout << "1. Verificar se a pilha está vazia.\n";
		cout << "2. Adicionar elemento (push).\n";
		cout << "3. Deletar elemento (pop).\n";
		cout << "4. Verificar elemento do topo.\n";
		cout << "5. Tamanho da pilha.\n";
		cout << "6. Ver se um elemento está na pilha.\n";
		cout << "7. Pegar elemento de uma posição. (O topo é o primeiro)\n";
		cout << "8. Limpar pilha.\n";
		cout << "9. Voltar.\n\n";

		int op;
		int elem, pos;
		cout << "Opcao: ";
		cin >> op;
		switch(op) {
			case 1:
				if(pilha.isEmpty())
					printf("Pilha vazia!\n");
				else printf("Pilha não vazia!\n");
				pressEnter();
				break;
			case 2:
				cout << "Informe o elemento que deseja inserir: ";
				cin >> elem;
				pilha.push(elem);
				break;
			case 3:
				pilha.pop();
				break;		
			case 4:
				cout << "O elemento do topo é: " << pilha.top() << endl;
				pressEnter();
				break;
			case 5:
				cout << "A pilha tem tamanho: " << pilha.size() << endl;
				pressEnter();
				break;
			case 6:
				cout << "Informe o elemento: ";
				cin >> elem;
				if(buscarElemento(elem, pilha))
					cout << "O elemento está na pilha!\n";
				else cout << "O elemento não está na pilha!\n";
				pressEnter();
				break;
			case 7:
				cout << "Informe a posição: ";
				cin >> pos;
				if(pos > 0 && pos <= pilha.size())
					cout << "O elemento é: " << pilha.pegarPosicao(pos) << endl;
				else cout << "Posição inexistente!\n";
				pressEnter();
				break;
			case 8:
				pilha.clear();
				break;
			case 9:
				leave = true;
				break;
			default:
				cout << "Opção não reconhecida.\n";
				pressEnter();
				break;
		}
	}
}


#endif
	/*
	ABOUT STACK DESTRUCTOR:
	It depends as to what data type your vector ie data is storing. If it is something like "vector<int>"
	or something that isn't a pointer then you needn't define the destructor as data would call the destructor
	for each of it's elements when it would call its own destructor.
	However if you are using vector<int*> or similar things where the pointers held by vector (ie data) are 
	holding variables on the heap (ie they are called using new keyword) then you need to explicitly write your 
	Stack destructor as :-
	~Stack()
	{
	     for (int i=0;i<data.size();++i)
	     {
	          delete data.at(i);  // or delete data[i]
	     }
	}
	}
	*/