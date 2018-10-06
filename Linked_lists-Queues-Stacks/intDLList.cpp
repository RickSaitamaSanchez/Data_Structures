#include <iostream>
#include "intDLList.h"
#include "interface.h"

using namespace std;

IntDLList::~IntDLList() {
	for(DLLNode *tmp; !isEmpty();) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}

void IntDLList::addToDLLHead(int el) {
	head = new DLLNode(el, head, 0);
	if(tail == 0)
		tail = head;
	else
		head->next->prev = head;
}

void IntDLList::addToDLLTail(int el) {
	if(tail != 0) {
		tail = new DLLNode(el,0,tail);
		tail->prev->next = tail;
	}
	else head = tail = new DLLNode(el);
}

void IntDLList::addToPos(int elem, int pos) {
	if(pos > 0 && pos <= listSize() + 1) {
		if(pos==1) 
			addToDLLHead(elem);
		else if(pos==listSize()+1)
			addToDLLTail(elem);
		else {
			DLLNode *tmp = head;
			DLLNode *node = new DLLNode(elem);
			for(int i = 1; i < pos; tmp=tmp->next, i++);
			tmp->prev->next = node;
			node->prev = tmp->prev;
			node->next = tmp;
			tmp->prev = node;
		}
	}
	else {
		cout << "Posição inexistente!\n";
		pressEnter();
	}
}

void IntDLList::deleteFromDLLHead() {
	if(head == tail) {
		if(!isEmpty()) delete head;
		head = tail = 0;
	}
	else {
		DLLNode *tmp = head;
		head = head->next;
		delete tmp;
	}
}

void IntDLList::deleteFromDLLTail() {
	if(head == tail) {
		if(!isEmpty()) delete head;
		head = tail = 0;
	}
	else {
		tail = tail->prev;
		delete tail->next;
		tail->next = 0;
	}
}

void IntDLList::deleteFromPos(int pos) {
	if(pos > 0 && pos <= listSize()) {
		if(pos==1)
			deleteFromDLLHead();
		else if(pos==listSize())
			deleteFromDLLTail();
		else {
			DLLNode *tmp = head;
			for(int i = 1; i != pos; i++, tmp=tmp->next);
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
		}
	} else {
		cout << "Posição inexistente!\n";
		pressEnter();
	}
}

void IntDLList::deleteDLLNode(int el) {
	if(head != 0)
		if(head == tail && el == head->info){
			delete head;
			head = tail = 0;
		}
		else if(el == head->info) {
			DLLNode *tmp = head;
			head = head->next;
			delete tmp;
			head->prev = 0;
		}
		else if(el == tail->info) {
			tail = tail->prev;
			delete tail->next;
			tail->next = 0;
		}
		else {
			DLLNode *tmp;
			for(tmp = head; (tmp != 0) && (tmp->info != el); tmp = tmp->next);
			if(tmp != 0) {
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				delete tmp;
			}
		}
}

bool IntDLList::isInList(int el) const {
	DLLNode *tmp;
	for(tmp = head; (tmp != 0) && (tmp->info != el); tmp = tmp->next);
	return tmp != 0;
}

int IntDLList::listSize() { 
	int size;
	DLLNode *tmp;
	for(tmp = head, size = 0; tmp != 0; tmp=tmp->next, size++);
	return size;
}

void IntDLList::printDLList() const {
	cout << "Elementos da lista: ";
	for(DLLNode *tmp = head; tmp != 0; tmp = tmp->next)
		cout << tmp->info << " ";
	cout << endl;
}

void menuDLL() {
	IntDLList lista;
	bool leave = false;
	while(!leave) {
		clearScreen();
		printHeader();
		cout << " ---------------->LISTA DUPLAMENTE ENCADEADA<---------------- \n";
		cout << " "; lista.printDLList();
		cout << " ------------------------------------------------------------ \n";
		cout << "1. Verificar se a lista está vazia.\n";
		cout << "2. Adicionar elemento ao head.\n";
		cout << "3. Adicionar elemento ao tail.\n";
		cout << "4. Adicionar elemento à posição específica\n";
		cout << "5. Deletar do head.\n";
		cout << "6. Deletar do tail.\n";
		cout << "7. Deletar de uma posição específica.\n";
		cout << "8. Deletar nó específico.\n";
		cout << "9. Verificar se elemento está na lista.\n";
		cout << "10. Voltar.\n\n";

		int op;
		int elem, pos;
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
				lista.addToDLLHead(elem);
				break;
			case 3:
				cout << "Informe o elemento que deseja inserir: ";
				cin >> elem;
				lista.addToDLLTail(elem);
				break;		
			case 4:
				cout << "Informe o elemento: ";
				cin >> elem;
				cout << "Informe a posição: ";
				cin >> pos;
				lista.addToPos(elem, pos);
				break;
			case 5:
				lista.deleteFromDLLHead();
				break;
			case 6:
				lista.deleteFromDLLTail();
				break;
			case 7:
				cout << "Informe a posição: ";
				cin >> pos;
				lista.deleteFromPos(pos);
				break;
			case 8:
				cout << "Informe o elemento que deseja excluir: ";
				cin >> elem;
				lista.deleteDLLNode(elem);
				break;
			case 9:
				cout << "Informe o elemento que deseja verificar: ";
				cin >> elem;
				if(lista.isInList(elem))
					cout << "Está na lista!\n";
				else cout << "Não está na lista!\n";
				pressEnter();
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
