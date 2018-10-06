#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

class IntSLLNode {
public:
	IntSLLNode() { next = 0; }
	IntSLLNode(int elem, IntSLLNode *ptr = 0) {
		info = elem;
		next = ptr;
	}
	int info;
	IntSLLNode *next;
};

class IntSLList {
public:
	IntSLList() {
		head = tail = 0;
	}
	~IntSLList();
	bool isEmpty() { return (head == 0); }
	void addToHead(int);
	void addToTail(int);
	void addToPos(int, int);
	void deleteFromHead();
	void deleteFromTail();
	void deleteNode(int);
	void deleteFromPos(int);
	int getElem(int);
	bool isInList(int) const;
	int listSize();
	void printList() const;
	int getHead();
	int getTail();
private:
	IntSLLNode *head, *tail;
};

void menuSLL();

#endif
