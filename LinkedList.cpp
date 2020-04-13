/**
 * @file LinkedList.cpp
 *
 * @brief Implementation of a Linked List
 *
 * @author Robin Viktorsson (robvik@hotmail.com)
 *
 * @date 2020-04-13 11:18
 */

#include <iostream>
#include <type_traits>

template<typename T>
bool isIntegralOrFloatingPoint(T value) {
	return (std::is_integral<T>::value || std::is_floating_point<T>::value);
}

template <class T>
class Node {
public:
	T data;
	Node* next;
};

template <class T>
class LinkedList {
public:
	LinkedList() {
		head = nullptr;
	}

	~LinkedList() {
		Node<T>* temp = head;

		while (head) {
			head = head->next;
			delete temp;
			temp = head;
		}
	};

	void addNode(T value);
	void display() const;
	void insertAtIndex(int index, T value, int listLength);
	void reverse();
	int count();
	T deleteAtIndex(int index, int listLength);
	T merge(LinkedList& list2);
	T sum();

private:
	Node<T>* head;
};

/**
 * Adds a new node to the linked list and points the last node to the new node
 *
 * @param value is the data value of the node
 */
template <class T>
void LinkedList<T>::addNode(T value) {
	Node<T>* node = new Node<T>();
	node->data = value;
	node->next = nullptr;

	if (head == nullptr) { // There is no node in the linked list yet
		head = node;
	} else {
		Node<T>* temp = head; // Save current head

		while (temp->next != nullptr) { // Get the last node in the linked list
			temp = temp->next;
		}

		temp->next = node; // Point the last node to the new node
	}
}

/**
 * Reverses the order of the nodes in the linked list
 */
template <class T>
void LinkedList<T>::reverse() {
	Node<T>* temp = head;
	Node<T>* nextNode = nullptr;
	Node<T>* reverseNode = nullptr;

	while (temp != nullptr) {
		head = temp;
		nextNode = temp->next;
		temp->next = reverseNode;
		reverseNode = temp;
		temp = nextNode;
	}
}

/**
 * Displays all nodes in the linked list
 */
template <class T>
void LinkedList<T>::display() const {
	if (head == nullptr) {
		std::cout << "List is empty!\n";
	} else {
		Node<T>* temp = head;
		while (temp != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->next;
		}

		std::cout << "\n";
	}
}

/**
 * Counts amount of nodes in the linked list
 *
 * @return counter which is amount of nodes
 */
template <class T>
int LinkedList<T>::count() {
	int counter = 0;

	Node<T>* temp = head;
	while (temp != nullptr) {
		counter++;
		temp = temp->next;
	}

	return counter;
}

/**
 * Sums the data values of all nodes
 *
 * @returns The sum of all the nodes' data values
 */
template <class T>
T LinkedList<T>::sum() {
	
	if (!isIntegralOrFloatingPoint(head->data)) {
		std::cout << "The type used is not an integer or floating point. There will be no summary.\n";
		return false;
	}
	
	int sum = 0;

	Node<T>* temp = head;
	while (temp != nullptr) {
		sum += temp->data;
		temp = temp->next;
	}

	return sum;
}

/**
 * Inserts a node at a specific index in the linked list
 *
 * @param index The index to insert the node at
 * @param value The data value of the new node
 * @param listLength The length of the list
 */
template <class T>
void LinkedList<T>::insertAtIndex(int index, T value, int listLength) {

	if (index < 0 || index > listLength) {
		std::cout << "You entered a negative number or a number that exceeded the length of the Linked List.\n";
		return;
	}

	Node<T>* p = head;
	Node<T>* temp = new Node<T>;
	temp->data = value;
	temp->next = nullptr;

	if (index == 0) {
		temp->next = head;
		head = temp;
	} else {
		for (int i = 0; i < index - 1; i++) {
			p = p->next;
		}

		temp->next = p->next;
		p->next = temp;
	}
}

/**
 * Deletes a node in the linked list at a specific index
 *
 * @param index The index of the linked list to delete
 * @param listLength The length of the list
 *
 * @return The deleted node's data value or -1 if the process failed.
 */
template <class T>
T LinkedList<T>::deleteAtIndex(int index, int listLength) {

	if (index < 0 || index > listLength) {
		std::cout << "You entered a negative number or a number that exceeded the length of the Linked List.\n";
		return false;
	}

	if (index == 0) {
		Node<T>* p = head;
		head = head->next;
		T value = p->data;
		delete p;

		return value;
	} else {
		Node<T>* p = head;
		Node<T>* q = nullptr;

		for (int i = 0; i < index - 1; i++) {
			q = p;
			p = p->next;
		}

		q->next = p->next;
		T value = p->data;
		delete p;

		return value;
	}
}

int main() {
	LinkedList<int> list;

	list.addNode(1);
	list.addNode(2);
	list.addNode(3);
	list.addNode(4);
	list.addNode(5);

	std::cout << "Linked List Data:\n";
	list.display(); // 1 2 3 4 5

	std::cout << "Reversing Linked List...\n";
	list.reverse(); 

	std::cout << "Reversed Linked List:\n";
	list.display(); // 5 4 3 2 1

	std::cout << "Reverse back...\n";
	list.reverse();
	list.display(); // 1 2 3 4 5

	std::cout << "Amount of nodes in the Linked List: " << list.count() << "\n"; // 5
	std::cout << "Sum of nodes data in the Linked List: " << list.sum() << "\n"; // 15

	std::cout << "Inserting a new node at index 0 with value 0\n";
	list.insertAtIndex(0, 0, list.count()); // 0 1 2 3 4 5

	std::cout << "Inserting a new node at the end of the list with value 6\n";
	list.insertAtIndex(list.count(), 6, list.count()); // 0 1 2 3 4 5 6

	std::cout << "Linked List Data: " << std::endl;
	list.display();

	std::cout << "Attempting to delete value 3 at index 4\n";
	auto del = list.deleteAtIndex(4, list.count());

	std::cout << "Linked List Data: \n";
	list.display();

	std::cout << "Inserting value 3 at index 3\n";
	list.insertAtIndex(3, 3, list.count());

	std::cout << "Linked List Data: \n";
	list.display();

	std::cout << "Inserting value 3 at index 3\n";
	list.insertAtIndex(3, 3, list.count());

	std::cout << "Linked List Data:\n" ;
	list.display();

	LinkedList<int> list2;
	list2.addNode(10);
	list2.addNode(11);
	list2.addNode(12);

	list2.display();

	return 0;
}
