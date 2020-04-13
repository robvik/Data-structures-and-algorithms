/**
 * @file QueueArray.cpp
 *
 * @brief Array-based queue without circular movement. Disadvantages: Once a space in the queue has been used, it can not be re-used.
 *
 * @author Robin Viktorsson (robvik@hotmail.com)
 *
 * @date 2020-04-13 10:28
 */
 
#include <iostream>

class Queue
{
public:
	Queue() {
		this->front = -1;
		this->rear = -1;
		this->size = 10;
		this->Q = new int[size];
	}

	Queue(int size) {
		this->front = -1;
		this->rear = -1;
		this->size = size;
		this->Q = new int[size];
	}

	~Queue() {
		delete this->Q;
	}

	void enqueue(int x);
	int dequeue();
	void display();

private:
	int front;
	int rear;
	int size;
	int *Q;
};

/**
 * Enqueues elements to the rear of the queue
 *
 * @param the value to add to the queue
 */
void Queue::enqueue(int value)
{
	if (rear == (size - 1)) {
		std::cout << "Queue is full." << std::endl;
	}
	else {
		rear++;
		Q[rear] = value;
	}
}

/**
 * Dequeues elements from the front in the queue
 *
 * @return The position of the element value that was removed or -1 if the queue is empty
 */
int Queue::dequeue()
{
	int x = -1;
	if (front == rear) {
		std::cout << "Queue is empty." << std::endl;
	}
	else {
		x = Q[front + 1];
		front++;
	}

	return x;
}

/**
 * Displays elements in the queue with values
 */
void Queue::display()
{
	for (int i = front + 1; i <= rear; i++) {
		std::cout << Q[i] << " ";
	}

	std::cout << std::endl;
}

int main()
{
	Queue q(5); // [  ][  ][  ][  ][  ]

	q.dequeue();   // Not possible - Queue is empty.
	q.enqueue(10); // [10][  ][  ][  ][  ]
	q.enqueue(20); // [10][20][  ][  ][  ]
	q.enqueue(30); // [10][20][30][  ][  ]
	q.dequeue();   // [  ][20][30][  ][  ]
	q.dequeue();   // [  ][  ][30][  ][  ]
	q.enqueue(40); // [  ][  ][30][40][  ]
	q.enqueue(50); // [  ][  ][30][40][50]
	q.enqueue(60); // Not possible - Queue is full.

	q.display();   // 30 40 50

	return 0;
}