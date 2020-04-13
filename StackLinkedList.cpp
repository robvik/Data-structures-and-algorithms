/**
 * @file StackLinkedList.cpp
 *
 * @brief Implementation of an linkedlist-based stack
 *
 * @author Robin Viktorsson (robvik@hotmail.com)
 *
 * @date 2020-04-13 11:12
 */

#include <iostream>
#include <optional>

template <class T>
class Node
{
public:
	Node* next;
	T data;
};

template <class T>
class Stack
{
private:
	Node<T>* top;

public:
	Stack() { 
		top = nullptr; 
	}

	void display();
	void push(T value);
	bool isEmpty();
	std::optional<T> pop();
};

/**
 * Pushes value to the stack
 *
 * @param value to push to the top of the stack
 */
template <class T>
void Stack<T>::push(T value)
{
	Node<T>* node = new Node<T>();
	node->data = value;
	node->next = top;
	top = node;

	std::cout << "Inserted value: " << value << " in the stack.\n";
}

/**
 * Pops value from the top of the stack
 *
 * @return the pooped value or -1 if there are no values in the stack
 */	
template <class T>
std::optional<T> Stack<T>::pop()
{
	std::optional<T> value = std::nullopt;
	if (!isEmpty()) {
		value = top->data;
		Node<T>* node = top;
		top = top->next;
		delete node;
	}

	return value;
}

/**
 * Checks if stack is empty
 *
 * @return true if empty, otherwise false
 */
template <class T>
bool Stack<T>::isEmpty() 
{
	return (top == nullptr);
}

/**
 * Displays all values in the stack
 */
template <class T>
void Stack<T>::display()
{
	Node<T>* node = this->top;
	while (node != nullptr) {
		std::cout << node->data << " ";
		node = node->next;
	}

	std::cout << "\n";
}

int main()
{
	Stack<int> stack;

	stack.push(10); // Inserted value : 10 in the stack.
	stack.push(20); // Inserted value : 20 in the stack.
	stack.push(30); // Inserted value : 30 in the stack.

	for (int i = 0; i < 5; i++) {
		auto pop = stack.pop();
		(!pop) ? 
			std::cout << "Stack is empty.\n" : 
			std::cout << "Removed value: " << pop.value() << " from stack.\n";
	}

	// Removed value : 30 from stack.
	// Removed value : 20 from stack.
	// Removed value : 10 from stack.
	// Stack is empty.
	// Stack is empty.

	stack.display();

	return 0;
}