/**
 * @file DoublyLinkedList.cpp
 *
 * @brief Implementation of an Doubly Linked List
 *
 * @author Robin Viktorsson (robvik@hotmail.com)
 *
 * @date 2020-04-13 11:17
 */

#include <iostream>

/**
 * Node Class
 */
template <class T>
class Node {
private: 
	T data;

public:
	Node(T data);
	~Node();

	Node* next;
	Node* prev;
	T getData();
};

template <class T>
Node<T>::Node(T data) {
	this->data = data;
}

template <class T>
Node<T>::~Node() {}

template <class T>
T Node<T>::getData() {
	return this->data;
}

/**
 * DoublyLinkedList Class
 */
template <class T>
class DoublyLinkedList {
private:
	T* head; // first node
	T* tail; // last node
	int size;

public:
	DoublyLinkedList();
	~DoublyLinkedList();

	void addTail(T* node); // Add last
	void addHead(T* node); // Add first
	void insertAfter(T* afterNode, T* newNode); // Insert after given node
	void insertBefore(T* beforeNode, T* newNode); // Insert before given node
	void insertAtIndex(int index, T* node); // Insert node at given index
	void reverse();
	void display();

	T* deleteHead();
	T* deleteTail();
	T* deleteAtIndex(int index);
	T* getIndex(int index);

	int getSize();
};

template <class T>
void DoublyLinkedList<T>::addTail(T* node) {
	node->next = nullptr;
	node->prev = nullptr;

	if (this->head == nullptr) {   // DLL is empty. Both head and tail will be the same
		this->head = node;         // Set head to the new node
		this->tail = this->head;   // Set tail to head (the new node)
	} else {
		this->tail->next = node;   // Point current tail to new tail
		node->prev = this->tail;   // Set prev to the old tail
		this->tail = node;		   // Set tail to the new node
	}

	this->size++; // Increase DLL size
}

template <class T>
void DoublyLinkedList<T>::addHead(T* node) {
	node->next = nullptr;
	node->prev = nullptr;

	if (this->head == nullptr) {    // DLL is empty. Both head and tail will be the same
		this->head = node;	        // Set head to the new node
		this->tail = this->head;    // Set tail to head (the new node)
	} else {
		this->head->prev = node;    // Set current heads prev to the new node
		node->next = this->head;    // Set the new nodes next to the old head
		this->head = node;          // Set head to the new node
	}

	this->size++; // Increase DLL size
}

template <class T>
void DoublyLinkedList<T>::insertAfter(T* afterNode, T* newNode) {

	if (afterNode == nullptr) {
		std::cout << "afterNode can not be nullptr.\n";
		return;
	}

	// Point next of the newNode to afterNode's next
	newNode->next = afterNode->next;

	// Point the prev of the new node to the afterNode
	newNode->prev = afterNode;

	// Point the prev of afterNode's next to the new node
	afterNode->next->prev = newNode;

	// Point afterNode's next to the new node
	afterNode->next = newNode;

	this->size++;
}

template <class T>
void DoublyLinkedList<T>::insertBefore(T* beforeNode, T* newNode) {
	
	if (beforeNode == nullptr) {
		std::cout << "beforeNode can not be nullptr.\n";
		return;
	}

	// Point next of the newNode to beforeNode
	newNode->next = beforeNode;

	// Point prev of newNode to beforeNode's prev
	newNode->prev = beforeNode->prev;

	// Point next of beforeNode's prev to newNode
	beforeNode->prev->next = newNode;

	// Point prev of beforeNode to newNode
	beforeNode->prev = newNode;

	this->size++;
}

template <class T>
void DoublyLinkedList<T>::insertAtIndex(int index, T* node) {

	if (index < 0 || index >= this->size) {
		std::cout << "Index is out of range.\n";
		return;
	}

	if (index == 0) {
		this->addHead(node);
	} else if (index == this->size) {
		this->addTail(node);
	} else {
		T* indexNode = this->getIndex(index);
		this->insertBefore(indexNode, node);
	}
}

template <class T>
void DoublyLinkedList<T>::display() {
	T* temp = this->head;

	if (temp == nullptr) {
		std::cout << "The DLL is empty.";
		return;
	}

	while (temp) {
		std::cout << temp->getData() << " ";
		temp = temp->next;
	}
}

template <class T>
T* DoublyLinkedList<T>::deleteHead() {
	if (this->head == nullptr) {
		std::cout << "Head is nullptr. Could not be deleted.\n";
		return nullptr;
	}

	T* temp = this->head;
	this->head = this->head->next; // Move current head to node in current head->next
	this->head->prev = nullptr;    // Set prev of new head to nullptr
	this->size--;                  // Decrement the size by 1
	return temp;				   // Return the dequeued node
}

template <class T>
T* DoublyLinkedList<T>::deleteTail() {
	if (this->tail == nullptr) {
		std::cout << "Tail is nullptr. Could not be deleted.\n";
		return nullptr;
	}

	T* temp = this->tail;
	this->tail = this->tail->prev;
	this->tail->next = nullptr;
	this->size--;
	return temp;
}

template <class T>
T* DoublyLinkedList<T>::deleteAtIndex(int index) {
	if (index < 0 || index >= this->size) {
		std::cout << "Index is out of range.\n";
		return nullptr;
	}

	if (index == 0) {
		return this->deleteHead();
	} else if (index == this->size) {
		return this->deleteTail();
	} else {
		T* deleteNode = this->getIndex(index);

		deleteNode->prev->next = deleteNode->next;
		deleteNode->next->prev = deleteNode->prev;

		deleteNode->prev = nullptr; // Is this necessary?
		deleteNode->next = nullptr; // Is this necessary?

		this->size--; // Decrement DLL size by 1

		return deleteNode;
	}
}

template <class T>
T* DoublyLinkedList<T>::getIndex(int index) {
	if (index == 0) {
		return this->head;
	} else if (index == this->size - 1) {
		return this->tail;
	} else if (index < 0 || index >= this->size) {
		std::cout << "Index is out of range.\n";
		return nullptr;
	} else {

		T* temp = this->head;

		int counter = 0;
		while (counter != index) {
			temp = temp->next;
			counter++;
		}

		return temp;
	}
}

template <class T>
void DoublyLinkedList<T>::reverse() {
	if (!this->size) {
		std::cout << "DLL is empty.\n";
		return;
	} 
	
	if (this->size == 1) {
		std::cout << "DLL consists of one node.\n";
		return;
	}

	T* currentHead = this->head;
	T* currentTail = this->tail;

	T* temp = this->head;
	while (temp != nullptr) {
		T* next = temp->next;
		temp->next = temp->prev;
		temp->prev = next;
		temp = next;
	}

	this->head = currentTail;
	this->tail = currentHead;
}

template <class T>
int DoublyLinkedList<T>::getSize() {
	return this->size;
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	while (this->head) {
		T* next = this->head->next;
		delete this->head;
		this->size = this->size - 1;
		this->head = next;
	}
}

int main()
{
	DoublyLinkedList<Node<int>> dll;

	dll.addHead(new Node<int>(1));     // 1
	dll.addTail(new Node<int>(2));     // 1 2

	auto insertAfter = new Node<int>(3);

	dll.addTail(insertAfter);	       // 1 2 3
	dll.addTail(new Node<int>(4));     // 1 2 3 4
	dll.addTail(new Node<int>(5));     // 1 2 3 4 5

	dll.insertAfter(insertAfter, new Node<int>(33)); // 1 2 3 33 4 5

	dll.addTail(new Node<int>(6));     // 1 2 3 33 4 5 6
	dll.addTail(new Node<int>(7));     // 1 2 3 33 4 5 6 7
	dll.addTail(new Node<int>(8));     // 1 2 3 33 4 5 6 7 8

	auto insertBefore = new Node<int>(9);

	dll.addTail(insertBefore);	       // 1 2 3 33 4 5 6 7 8 9
	dll.addTail(new Node<int>(10));    // 1 2 3 33 4 5 6 7 8 9 10

	dll.insertBefore(insertBefore, new Node<int>(99)); // 1 2 3 33 4 5 6 7 8 99 9 10

	dll.insertAtIndex(10, new Node<int>(999)); // 1 2 3 33 4 5 6 7 8 99 999 9 10

	auto del1 = dll.deleteAtIndex(3);     // 1 2 3 4 5 6 7 8 99 999 9 10
	std::cout << "Deleted: " << del1->getData() << "\n"; // 33

	auto del2 = dll.deleteAtIndex(8);     // 1 2 3 4 5 6 7 8 999 9 10
	std::cout << "Deleted: " << del2->getData() << "\n"; // 99

	auto del3 = dll.deleteAtIndex(8);     // 1 2 3 4 5 6 7 8 9 10
	std::cout << "Deleted: " << del3->getData() << "\n"; // 999

	dll.deleteHead();	// 2 3 4 5 6 7 8 9 10
	dll.deleteTail();	// 2 3 4 5 6 7 8 9

	dll.reverse();		// 9 8 7 6 5 4 3 2

	dll.deleteHead();   // 8 7 6 5 4 3 2
	dll.deleteHead();   // 7 6 5 4 3 2
	dll.deleteTail();   // 7 6 5 4 3
	dll.deleteTail();   // 7 6 5 4

	dll.reverse();		// 4 5 6 7

	dll.addHead(new Node<int>(3)); // 3 4 5 6 7
	dll.addHead(new Node<int>(2)); // 2 3 4 5 6 7
	dll.addHead(new Node<int>(1)); // 1 2 3 4 5 6 7
	dll.addHead(new Node<int>(0)); // 0 1 2 3 4 5 6 7

	dll.addTail(new Node<int>(8)); // 0 1 2 3 4 5 6 7 8
	dll.addTail(new Node<int>(9)); // 0 1 2 3 4 5 6 7 8 9

	dll.display();

	std::cout << "\nSize of DLL: " << dll.getSize() << "\n";

	return 0;
}
