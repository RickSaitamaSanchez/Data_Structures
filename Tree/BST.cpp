#include "genBST.h"

int main() {

	BST<int> arvore;
	int v[] = {13,10,2,12,25,20,31,29,15,7,40,23};
	for(int i = 0; i <= 11; i++)
		arvore.add(v[i]);
	arvore.print();
	return 0;
}