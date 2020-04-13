/**
 * @file CircularQueue.cpp
 *
 * @brief Implementation of a circular queue
 *
 * @author Robin Viktorsson (robvik@hotmail.com)
 *
 * @date 2020-04-13 10:55
 */

#include <iostream>

class CircularQueue
{
public:
	CircularQueue() {
		this->front = -1;
		this->rear = -1;
		this->size = 10;
		this->Q = new int[this->size];
	}

	CircularQueue(int value) {
		this->front = -1;
		this->rear = -1;
		this->size = value;
		this->Q = new int[value];
	}

	~CircularQueue() {
		delete this->Q;
	}

	void enqueue(int value);
	int dequeue();
	void display();
	bool isEmpty();
	bool isFull();

private:
	int size;
	int front;
	int rear;
	int *Q;
};

/**
 * Enqueues value in the circular queue
 *
 * @param value to insert into the queue
 */
void CircularQueue::enqueue(int value)
{
	if (isFull()) {
		std::cout << "Queue is full" << std::endl;
	} else {
		if (front == -1) { // If there are no values in the circular queue
			front = 0;
		}

		rear = (rear + 1) % size; // Move the rear one step to the right
		Q[rear] = value;

		std::cout << "Inserted: " << value << std::endl;
	}
}

/**
 * Dequeue value from the queue (front)
 *
 * @return the dequeued value or -1 if there are no values in the queue
 */
int CircularQueue::dequeue()
{
	if (isEmpty()) {
		std::cout << "Queue is empty." << std::endl;
		return -1;
	} else {
		int value = Q[front]; // Get value to be dequeued
		if (front == rear) { // The circular queue only has one element, so lets reset the circular queue
			front = -1;
			rear = -1;
		} else {
			front = (front + 1) % size;
		}

		std::cout << "Deleted value: " << value << std::endl;
		return value;
	}
}

/**
 * Display all values in the circular queue in both actual order and normal order
 */
void CircularQueue::display()
{
	if (isEmpty()) {
		std::cout << "Queue is empty." << std::endl;
	} else {
		std::cout << "Items in queue order: ";
		
		int i;
		for (i = front; i != rear; i = (i + 1) % size) {
			std::cout << Q[i] << " ";
		}

		std::cout << Q[i] << std::endl;

		std::cout << "Items in actual order: ";
		for (int j = 0; j < size; j++) {
			std::cout << Q[j] << " ";
		}
	}
}

/**
 * Check if circular queue is full.
 *
 * The circular queue is full if: 
 * - front is at the first element and rear is at the last element in the array
 * - front is attempting to pass the rear
 *
 * @return true if full, otherwise empty
 */
bool CircularQueue::isFull() {
	return ((front == rear + 1) || (front == 0 && rear == size - 1));
}

/**
 *	Check if circular queue is empty
 *
 *  @return true if empty, otherwise false
 */
bool CircularQueue::isEmpty() {
	return (front == -1);
}

int main()
{
	CircularQueue q(5); // [  ][  ][  ][  ][  ]

	q.enqueue(10); // [10][  ][  ][  ][  ]
	q.enqueue(20); // [10][20][  ][  ][  ]
	q.enqueue(30); // [10][20][30][  ][  ]
	q.enqueue(40); // [10][20][30][40][  ]
	q.enqueue(50); // [10][20][30][40][50]
	q.enqueue(60); // Not working - Queue is full!
	q.dequeue();   // [  ][20][30][40][50]
	q.enqueue(70); // [70][20][30][40][50]
	q.dequeue();   // [70][  ][30][40][50]
	q.enqueue(80); // [70][80][30][40][50]
	
	q.display();

	return 0;
}