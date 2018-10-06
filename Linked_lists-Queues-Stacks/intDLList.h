#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

class DLLNode {
public:
	DLLNode() {next = prev = 0;}
	DLLNode(int el, DLLNode *n = 0, DLLNode *p = 0) {
		info = el; next = n; prev = p;
	}
	int info;
	DLLNode *next, *prev;
};

class IntDLList {
public:
	IntDLList() { head = tail = 0; }
	~IntDLList();
	bool isEmpty() { return (head == 0); }
	void addToDLLHead(int el);
	void addToDLLTail(int el);
	void addToPos(int, int);
	void deleteFromDLLHead(); 
	void deleteFromDLLTail(); 
	void deleteFromPos(int);
	void deleteDLLNode(int);
	bool isInList(int) const;
	int listSize();
	void printDLList() const;
protected:
	DLLNode *head, *tail;
};

void menuDLL();

#endif