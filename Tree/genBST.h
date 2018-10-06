#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <iostream>
#include <iomanip>
#include "auxMethods.h"

using namespace std;

template<class T>
class Node {
public:
	T data;
	Node *left;
	Node *right;
	Node(T& d) { 
		data = d;
		left = 0;
		right = 0;
	}
	Node(T& d, Node<T> *l, Node<T> *r) {
		data = d;
		left = l;
		right = r;
	}
};

template<class T>
class BST {
public:
	BST() { root = 0; }
	~BST() { clear(); }
	void add(T& val) { add(val, root); }
	void clear() { clearTree(root); root = 0; }
	void print() { print(root, 0); }
	// int nodesCount();
	// int height();
	// T deleteValue(T val);
	bool isEmpty() { return root == 0; }
private:
	void add(T& val, Node<T> *n);
	void clearTree(Node<T> *n);
	void print(Node<T> *n, int indent);
	Node<T> *root;
};

template<class T>
void BST<T>::add(T& val, Node<T> *n) { // Parâmetro Node definido para root como padrão, para começar o processo da raiz.
	if(n != 0) { // Se houver raiz (obs: esta comparação só vai possivelmente falhar numa raiz, e nunca num nó qualquer abaixo...
		// entrando em qualquer dos casos abaixo a comparação se o filho é nulo já é feita previamente e solucionada)
		if (val < n->data) { // Se o valor for menor que o do nó, vai colocar à esquerda.
			if(n->left == 0) // Se o nó não tiver nenhum filho à esquerda
				n->left = new Node<T>(val); // Cria um nó à esquerda com o valor 
			else add(val, n->left); // Se já tiver, refaz o processo com o nó da esquerda.
		} else if (val > n->data) { // Se o valor for maior que o valor do nó, vai colocar à direita.
			if(n->right == 0)
				n->right = new Node<T>(val);
			else add(val, n->right);
		} else { // se o valor for igual ao do nó
			cout << "O valor já está presente na àrvore!" << endl;
			pressEnter();
		}
	} else {
		root = new Node<T>(val); // Se ainda não houver raiz:
	}
}

template<class T>
void BST<T>::clearTree(Node<T> *n) {
	if(n != 0) { // Se um nó for não nulo:
		if(n->right != 0) // Se houver um nó à direita
			clearTree(n->right); // Chama clear para a sub-árvore dá direita
		if(n->left != 0) 
			clearTree(n->left);
		delete n; // Após limpar, recursivamente, tudo abaixo de cada nó, deleta o nó.
		n = 0; // faz com que aponte para NULL
	}
}

template<class T>
void BST<T>::print(Node<T> *n, int indent = 0) {
	if(n != 0) {
		if(n->right != 0) print(n->right, indent+4);
		if(indent) cout << setw(indent) << ' ';
		if(n->right != 0) cout << " /\n" << setw(indent) << ' ';
		cout << n->data << "\n ";
		if(n->left != 0) {
			cout << setw(indent) << ' ' << 	" \\\n";
			print(n->left, indent+4);
		}
	}
}

#endif