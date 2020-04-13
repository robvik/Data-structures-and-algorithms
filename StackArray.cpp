/**
 * @file StackArray.cpp
 *
 * @brief Implementation of an array-based stack
 *
 * @author Robin Viktorsson (robvik@hotmail.com)
 *
 * @date 2020-04-13 11:10
 */

#include <iostream>

template<class T>
class Stack
{
private:
	T *stack;
	int size;
	int top;

public:
	Stack() { 
		this->size = 10; 
		this->top = -1; 
		this->stack = new T[this->size]; 
	}

	Stack(int size) {
		this->size = size; 
		this->top = -1;
		this->stack = new T[this->size];
	}

	void push(T value);
	void display();

	T pop();
	T peek(int index);

	int isEmpty();
	int isFull();
};

/**
 * Pushes value to the stack
 *
 * @param value to push to the top of the stack
 */
template<class T>
void Stack<T>::push(T value)
{
	if (isFull()) {
		std::cout << "Stack is full.\n";
	} else {
		std::cout << "Inserting value: " << value << "\n";
		top++;
		stack[top] = value;
	}
}

/**
 * Pops value from the top of the stack
 *
 * @return the pooped value or -1 if there are no values in the stack
 */
template<class T>
T Stack<T>::pop()
{
	T value = -1;
	if (isEmpty()) {
		std::cout << "Stack is empty.\n";
	} else {
		value = stack[top];
		std::cout << "Removing value: " << value << "\n";
		top--;
	}

	return value;
}

/**
 * Peeks a value in the stack based on index
 *
 * @param the index of the stack to peek
 * @return the peeked value or -1 if there are no values in the stack
 */
template<class T>
T Stack<T>::peek(int index)
{
	T value = -1;
	if (top - index + 1 < 0) {
		std::cout << "Index out of range.\n";
	} else {
		value = stack[top - index + 1];
	}

	return value;
}

/**
 * Checks if stack is full
 *
 * @return true if full, otherwise false
 */
template<class T>
int Stack<T>::isFull()
{
	return top == size - 1;
}

/**
 * Checks if stack is empty
 *
 * @return true if empty, otherwise false
 */
template<class T>
int Stack<T>::isEmpty()
{
	return top == -1;
}

/**
 * Displays all values in the stack
 */
template<class T>
void Stack<T>::display()
{
	for (int i = top; i >= 0; i--) {
		std::cout << stack[i] << " ";
	}
	
	std::cout << "\n";
}

int main()
{
	Stack<char> stack(5);
	stack.push('a'); // a
	stack.push('b'); // b a
	stack.push('c'); // c b a
	stack.push('d'); // d c b a
	stack.push('e'); // e d c b a
	stack.push('f'); // Stack is full. Value will not get added.

	stack.pop();

	stack.display(); // d c b a

	std::cout << stack.peek(1) << "\n"; // d

	return 0;
}