#include <iostream>
#include <stdio.h>
#include "intSLList.h"
#include "interface.h"

using namespace std;

IntSLList::~IntSLList() { // Destructor
	for (IntSLLNode *p; !isEmpty(); ) { // Enquanto a lista não estiver vazia
		p = head->next; // armazena o sucessor do head
		delete head;
		head = p; // e faz com que o head, após apagado, seja seu antigo sucessor
	}
}

void IntSLList::addToHead(int elem) {
	head = new IntSLLNode(elem, head); // o head agora recebe um nó que contém o elemento e o endereço para o antigo head.
	if(tail == 0) // Se a lista estava vazia e agora contém um elemento
		tail = head; // faz com que a cauda seja igual ao único elemento (que também é o head)
}

void IntSLList::addToTail(int elem) {
	if (tail != 0) { // se a lista não estiver vazia
		tail->next = new IntSLLNode(elem); // o antigo tail vai agora apontar para o novo tail
		tail = tail->next;
	}
	else head = tail = new IntSLLNode(elem);
}

void IntSLList::addToPos(int elem, int pos) { // Adicionar elemento a uma posição específica.
	// OBS: Esta função só adiciona o elemento se a posição, na lista, for existente.
	// Por exemplo, não se pode adicionar na posição 5 se a lista tiver tamanho 3.
	if(pos==1)
		addToHead(elem);
	else if(pos == listSize()+1) 
		addToTail(elem);
	else if(pos <= listSize() && pos != 0) { // Coloca o elemento na posição exata inserida. Por exemplo, a posição 2 é logo após o head.
		IntSLLNode *prev = head;
		IntSLLNode *tmp = new IntSLLNode(elem);
		int i;
		for(i = 1; i < pos-1; prev=prev->next, i++); // Neste for o 'prev' vai até a posição anterior à da posição requisitada.
		tmp->next = prev->next; // prev->next vai agora estar em pos + 1, e tmp vai estar em pos.
		prev->next = tmp;
	}
	else {
		cout << "Posição inexistente!\n";
		pressEnter();
	}
}

void IntSLList::deleteFromHead() { // Deleta da cabeça
	if (head == tail) { // Caso só tenha 1 elemento ou 0
		if(!isEmpty()) delete head; // se tiver 1, deleta o head, pois caso tenha 0, estaremos tentando deletar nullptr
		head = tail = 0; // head e tail vão ser nullptr agora.
	}
	else {
		IntSLLNode *tmp;
		tmp = head; // guarda o ponteiro para o head
		head = head->next; // o head agora é seu sucessor
		delete tmp; // deleta o head antigo.
	}
}

void IntSLList::deleteFromTail() { // deletar da cauda
	if(head == tail) {
		if(!isEmpty()) delete head;
		head = tail = 0;
	}
	else {
		IntSLLNode *tmp;
		for (tmp = head; tmp->next != tail; tmp = tmp->next); // percorre até o nó que aponta para a cauda
		delete tail;
		tail = tmp; // faz com que ele seja a nova cauda, após deletar a antiga.
		tail->next = 0;
	}
}

void IntSLList::deleteNode(int elem) { // deleta a primeira ocorrência de um elemento na lista.
	if (head != 0) // se a lista não estiver vazia
		if (head == tail && elem == head->info) { // se só tiver 1 nó na lista
			delete head;
			head = tail = 0;
		}
		else if (elem == head->info) { // se o elemento estiver na cabeça (com mais de 1 elemetno na lista)
			IntSLLNode *tmp = head;
			head = head->next;
			delete tmp; // faz o mesmo que deleteFromHead()
		}
		else { // caso tiver mais de um elemento, e o escolhido não ser o primeiro
			IntSLLNode *pred, *tmp; // Para uma posição e sua sucessora
			for (pred = head, tmp = head->next; 
			tmp != 0 && !(tmp->info == elem); // até tmp chegar no elemento
			pred = pred->next, tmp = tmp->next); 
			if (tmp != 0) { // se tmp==0 quer dizer que passou da cauda e não encontrou o elemento.
				pred->next = tmp->next; // o atributo next do predecessor ao elemento vai apontar para o sucessor do elemento
				if(tmp == tail) // se o elemento estiver na cauda devemos atualizar a cauda.
					tail = pred;
				delete tmp; // deleta o nó que contém o elemento
			}
		}
}

void IntSLList::deleteFromPos(int pos) {
	if(pos>0 && pos <= listSize()) { // Se for escolhida uma posição existente na lista
		if(pos==1)
			deleteFromHead();
		else if(pos==listSize())
			deleteFromTail();
		else { // se a posição for entre o primeiro elemento e a cauda (intervalo aberto)
			IntSLLNode *tmp, *tmp2;
			int i;
			for(tmp=head, i=1; i < pos-1; tmp=tmp->next, i++); // um nó auxiliar percorre a lista até a posição anterior à desejada.
			tmp2 = tmp->next; // tmp2 recebe o nó a ser deletado
			tmp->next = tmp2->next; // o antecessor vai apontar para o sucessor do nó a ser deletado
			delete tmp2;
		}
	} else {
		cout << "Posição inexistente nesta lista.\n";
		pressEnter();
	}
}

int IntSLList::getElem (int pos) { // Pega o elemento de determinada posição
	if(!isEmpty() && pos <= listSize()) { 
		IntSLLNode *tmp;
		int i;
		for(tmp=head, i = 0; i < pos-1 && tmp != 0; i++, tmp=tmp->next); // Percorre a lista até a posição
		return tmp->info; // retorna o valor que contém nesse nó
	} else return 0; // se a lista estiver vazia ou a posição estiver após o final da lista, retorna 0 (como se fosse nulo o elemento)
}

bool IntSLList::isInList (int elem) const { // Verifica se o elemento está na lista
	IntSLLNode *tmp;
	for (tmp = head; tmp != 0 && !(tmp->info == elem); tmp = tmp->next); // Percorre até o final ou até encontrar o elemento
	return tmp != 0; // se chegou no final quer dizer que não encontrou.
}

void IntSLList::printList() const { // Método auxiliar pra printar a lista.
	IntSLLNode *tmp;
	cout << " ";
	for(tmp = head; tmp != 0; tmp = tmp->next) {
		printf("%d ", tmp->info);
	}
	cout << endl;
}

int IntSLList::listSize() { // retorna o tamanho da lista.
	int size;
	IntSLLNode *tmp;
	for(tmp = head, size = 0; tmp != 0; tmp=tmp->next, size++);
	return size;
}

// Os métodos abaixo foram implementados para a utilização em fila e pilhas.
// O ideal seria usar o removeFromHead() e removeFromTail() retornando o elemento
// removido. No entando, para deixar o menu mais simples e a lista mais manipulável
// para alguma aplicação real, foi implementado desta forma. Fique ressaltado que
// as estruturas de dados continuam fazendo necessariamente apenas o que devem
// fazer por definição.
int IntSLList::getHead() { if(!isEmpty()) return head->info; }
int IntSLList::getTail() { if(!isEmpty()) return tail->info; }

void menuSLL() {
	IntSLList lista;
	bool leave = false;
	while(!leave) {
		clearScreen();
		printHeader();
		cout << " ------------------>LISTA ENCADEADA SIMPLES<------------------ \n";
		cout << " "; lista.printList();
		cout << " ------------------------------------------------------------- \n";
		cout << "1. Verificar se a lista está vazia.\n";
		cout << "2. Adicionar elemento ao head.\n";
		cout << "3. Adicionar elemento ao tail.\n";
		cout << "4. Adicionar elemento à posição específica.\n";
		cout << "5. Deletar do head.\n";
		cout << "6. Deletar do tail.\n";
		cout << "7. Deletar nó específico (pelo elemento).\n";
		cout << "8. Deletar nó específico (pela posição).\n";
		cout << "9. Verificar elemento de uma posição.\n";
		cout << "10. Verificar se um elemento está na lista.\n";
		cout << "11. Ver tamanho da lista.\n";
		cout << "12. Voltar.\n\n";

		int op;
		int elem, pos;
		cout << "Opcao: ";
		cin >> op;
		switch(op) {
			case 1:
				if(lista.isEmpty())
					printf("Lista vazia!\n");
				else printf("Lista não vazia!\n");
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
				cout << "Informe o elemento que deseja inserir: ";
				cin >> elem;
				cout << "Informe a posição que deseja inserir: ";
				cin >> pos;
				lista.addToPos(elem, pos);
				break;
			case 5:
				lista.deleteFromHead();
				break;
			case 6:
				lista.deleteFromTail();
				break;
			case 7:
				cout << "Informe o elemento que deseja excluir: ";
				cin >> elem;
				lista.deleteNode(elem);
				break;
			case 8:
				cout << "Informe a posição: ";
				cin >> pos;
				lista.deleteFromPos(pos);
				break;
			case 9:
				cout << "Informe a posição: ";
				cin >> pos;
				cout << "O elemento é: " << lista.getElem(pos) << endl;
				pressEnter();
				break;
			case 10:
				cout << "Informe o elemento que deseja verificar: ";
				cin >> elem;
				if(lista.isInList(elem))
					cout << "Está na lista!\n";
				else cout << "Não está na lista!\n";
				pressEnter();
				break;
			case 11:
				cout << "A lista tem tamanho: " << lista.listSize() << endl;
				pressEnter();
				break;
			case 12:
				leave = true;
				break;
			default:
				cout << "Opção não reconhecida.\n";
				pressEnter();
				break;
		}
	}
}

















//
