#ifndef QUEUE
#define QUEUE

#include "interface.h"
#include "intSLList.h"

using namespace std;

class Queue { 
public:
	Queue(int s=10) {size=s;} // Fila de tamanho fixo.
	~Queue() { while(!isEmpty()) dequeue(); }
	void enqueue(int);
	int dequeue();
	bool isFull() { return storage.listSize()==size; }
	bool isEmpty() { return storage.isEmpty(); }
	int firstEl() { return storage.getHead(); }
	bool searchEl(int);
	int getPos(int);
	int getSize();
	void clear() { while(!isEmpty()) dequeue(); } // Tira o primeiro elemento até ficar vazia.
	void printQueue() {	storage.printList(); }
private:
	int size;
	IntSLList storage;
};

void Queue::enqueue(int el) { 
	if(!isFull()) // Se a fila não estiver cheia
		storage.addToTail(el);  // Coloca o novo elemento no final da fila
	else {
		cout << "A fila está cheia!\n"; 
		pressEnter();
	}
}

int Queue::dequeue() {
	int x = storage.getHead();
	storage.deleteFromHead(); // Tira o primeiro elemento da fila. 
	return x; // retorna o valor do elemento.
}

bool Queue::searchEl(int el) {
	Queue aux;
	bool flag = 0;
	while(!isEmpty()) { // preenche a fila auxiliar com todos os elementos da fila original (para, no final, manter a ordem).
		if(firstEl()==el)
			flag=1; // se encontrou o elemento, ativa a flag.
		aux.enqueue(dequeue());
	}
	while(!aux.isEmpty())
		enqueue(aux.dequeue()); // Devolve os elementos para fila original
	return flag;
}

int Queue::getPos(int pos) {
	Queue aux;
	int x;
	for(int i = 1; !isEmpty(); i++, aux.enqueue(dequeue())) { // passa tudo para a fila auxiliar
		if(i==pos)
			x = firstEl(); // se chegou na posição desejada, pega o elemento dela.
	}
	while(!aux.isEmpty())
		enqueue(aux.dequeue()); // devolve tudo para a fila original
	return x;
}

int Queue::getSize() {
	Queue aux;
	int size;
	for(size=0; !isEmpty(); aux.enqueue(dequeue()), size++); // incrementa size tirando os elementos da fila
	while(!aux.isEmpty()) enqueue(aux.dequeue()); // devolve os elementos para a fila.
	return size;	
}

void menuQueue() {
	Queue fila(5); // declara uma fila de tamanho máximo 5.
	bool leave = false;
	while(!leave) {
		clearScreen();
		printHeader();
		cout << " ---------------------------> FILA <-------------------------- \n";
		cout << " "; fila.printQueue();
		cout << " ------------------------------------------------------------- \n";
		cout << "1. Adicionar elemento.\n";
		cout << "2. Deletar elemento.\n";
		cout << "3. Verificar se a fila está cheia.\n";
		cout << "4. Verificar se a fila está vazia.\n";
		cout << "5. Ver quem é o primeiro elemento.\n"; 
		cout << "6. Procurar elemento na fila.\n";
		cout << "7. Pegar elemento de uma posição.\n";
		cout << "8. Tamanho atual da fila.\n";
		cout << "9. Limpar fila.\n";
		cout << "10. Voltar.\n\n";

		int op;
		int elem, pos;
		cout << "Opcao: ";
		cin >> op;
		switch(op) {
			case 1:
				cout << "Informe o elemento que deseja inserir: ";
				cin >> elem;
				fila.enqueue(elem);
				break;
			case 2:
				fila.dequeue();
				break;
			case 3:
				(fila.isFull()) ? cout << "Fila cheia!\n" : cout << "A fila não está cheia!\n";
				pressEnter();
				break;		
			case 4:
				(fila.isEmpty()) ? cout << "Fila vazia!\n" : cout << "A fila não está vazia!\n";
				pressEnter();
				break;
			case 5:
				cout << "O primeiro elemento é: " << fila.firstEl() << endl;
				pressEnter();
				break;
			case 6:
				cout << "Informe o elemento que deseja procurar: ";
				cin >> elem;
				if(fila.searchEl(elem))
					cout << "O elemento está na fila!\n";
				else cout << "O elemento não está na fila!\n";
				pressEnter();
				break;
			case 7:
				cout << "Informe a posição: ";
				cin >> pos;
				if(pos>0 && pos<=fila.getSize())
					cout << "O elemento é: " << fila.getPos(pos) << endl;
				else cout << "Posição inexistente!\n";
				pressEnter();
				break;
			case 8:
				cout << "A fila tem tamanho: " << fila.getSize() << endl;
				pressEnter();
				break;
			case 9:
				fila.clear();
				break;
			case 10:
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