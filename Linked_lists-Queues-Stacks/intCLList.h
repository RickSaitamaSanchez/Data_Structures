#ifndef CIRCULAR_LINKED_LIST
#define CIRCULAR_LINKED_LIST

#include "interface.h"

// A lista circular já havia sido implementada anteriormente à requisição formal do trabalho.
// Por isto, pode faltar alguns métodos como o de deletar uma posição específica.

class CLLNode {
public:
	CLLNode() { next = prev = 0; }
	CLLNode(int el, CLLNode *n=0, CLLNode *p=0) { info=el; next=n; prev=p; }
	int info;
	CLLNode *next, *prev;
};

class IntCLList {
public:
	IntCLList() { tail=0; }
	~IntCLList();
	bool isEmpty() { return tail==0; }
	void addToTail(int);
	void addToHead(int);
	void deleteFromHead();
	void deleteFromTail();
	int listSize();
	void deleteNode(int);
	bool isInList(int);
	void printList();
protected:
	CLLNode *tail;
};

IntCLList::~IntCLList() {
	while (!isEmpty()) {
		deleteFromTail();
	}
}

void IntCLList::addToTail(int el) {
	if(isEmpty()){
		tail = new CLLNode(el);
		tail->next = tail;
		tail->prev = tail;
	} else {
		tail->next = new CLLNode(el, tail->next, tail);
		tail = tail->next;
		tail->next->prev = tail;
	}
}

void IntCLList::addToHead(int el) {
	if(isEmpty()) {
		tail = new CLLNode(el);
		tail->next = tail;
		tail->prev = tail;
	} else {
		tail->next = new CLLNode(el, tail->next, tail);
		tail->next->next->prev = tail->next;
	}
}

void IntCLList::deleteFromHead() {
	if(tail!=0) {
		if(tail->next!=tail) {
			CLLNode *tmp = tail->next;
			tail->next->next->prev = tail;
			tail->next = tail->next->next;
			delete tmp;
		} else {
			delete tail;
			tail = 0;
		}
	}
}

void IntCLList::deleteFromTail() {
	if(tail!=0) {
		if(tail->next!=tail) {
			CLLNode *tmp = tail;
			tail->prev->next = tail->next;
			tail->next->prev = tail->prev;
			tail = tail->prev;
			delete tmp;
		} else {
			delete tail;
			tail = 0;
		}
	}
}

int IntCLList::listSize() {
	if(tail!=0) {
		int size = 1;
		for(CLLNode *tmp = tail->next; tmp!=tail; tmp=tmp->next, size++);
		return size;
	} else return 0;
}

void IntCLList::deleteNode(int el) {
	if(tail!=0) {
		CLLNode *tmp;
		for(tmp = tail->next; tmp->info != el && tmp!=tail; tmp=tmp->next);
		if(tmp->info==el){
			if(tail->next!=tail){
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				if(tmp==tail)
					tail = tmp->prev;
				delete tmp;
			} else {
				delete tail;
				tail=0;
			}
		}
	}
}

bool IntCLList::isInList(int el) {
	if(tail!=0) {
		CLLNode *tmp;
		for(tmp = tail->next; tmp->info!=el && tmp!=tail; tmp=tmp->next);
		if(tmp->info==el)
			return 1;
	} 
	return 0;
}

void IntCLList::printList() {
	cout << "Elementos da lista: ";
	if(!isEmpty())
		for(CLLNode *tmp = tail->next; ; tmp=tmp->next) {
			cout << tmp->info << ' ';
			if(tmp==tail)
				break;
		}
	cout << endl;
}

void menuCLL() {
	IntCLList lista;
	cout << "Construtor worked!\n";
	bool leave = false;
	while(!leave) {
		clearScreen();
		printHeader();
		cout << " ----------------> LISTA ENCADEADA CIRCULAR <---------------- \n";
		cout << " "; lista.printList();
		cout << " ------------------------------------------------------------ \n";
		cout << "1. Verificar se a lista está vazia.\n";
		cout << "2. Adicionar elemento ao head.\n";
		cout << "3. Adicionar elemento ao tail.\n";
		cout << "4. Deletar do head.\n";
		cout << "5. Deletar do tail.\n";
		cout << "6. Deletar nó específico.\n";
		cout << "7. Verificar se elemento está na lista.\n";
		cout << "8. Verificar tamanho da lista.\n";
		cout << "9. Voltar.\n\n";

		int op;
		int elem;
		cout << "Opcao: ";
		cin >> op;
		switch(op) {
			case 1:
				if(lista.isEmpty())
					cout << "Lista vazia!\n";
				else cout << "Lista não vazia!\n";
				pressEnter();
				break;
			case 2:
				cout << "Informe o elemento que deseja inserir: ";
				cin >> elem;
				lista.addToHead(elem);
				break;
			case 3:
				cout << "Informe o elemento que deseja inserir: ";
				cin >> elem;
				lista.addToTail(elem);
				break;		
			case 4:
				lista.deleteFromHead();
				break;
			case 5:
				lista.deleteFromTail();
				break;
			case 6:
				cout << "Informe o elemento que deseja excluir: ";
				cin >> elem;
				lista.deleteNode(elem);
				break;
			case 7:
				cout << "Informe o elemento que deseja verificar: ";
				cin >> elem;
				if(lista.isInList(elem))
					cout << "Está na lista!\n";
				else cout << "Não está na lista!\n";
				pressEnter();
				break;
			case 8:
				cout << "A lista tem tamanho: " << lista.listSize() << endl;
				pressEnter();
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