/**
 * @file BinaryTreeQueue.cpp
 *
 * @brief Implementation of a binary tree queue
 *
 * @author Robin Viktorsson (robvik@hotmail.com)
 *
 * @date 2020-04-13 11:01
 */

#include <iostream>

template <class T>
class Node {
public:

	Node() {}

	Node(T value) 
	{
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}

	T value;
	Node* left;
	Node* right;
};

template <class T>
class BinaryTree {
public:
	BinaryTree();

	void insert(T key);
	Node<T>* search(T key);

private:
	void insert(T key, Node<T>* leaf);
	Node<T>* search(T key, Node<T>* leaf);

	Node<T> *root;
};

template <class T>
BinaryTree<T>::BinaryTree() 
{
	this->root = nullptr;
}

// Recursive
template <class T>
void BinaryTree<T>::insert(T key, Node<T>* leaf) 
{
	if (key < leaf->value) {
		if (leaf->left != nullptr) {
			insert(key, leaf->left);
		} else {
			leaf->left = new Node<T>();
			leaf->left->value = key;
			leaf->left->left = nullptr;
			leaf->left->right = nullptr;
		}
	} else {
		if (leaf->right != nullptr) {
			insert(key, leaf->right);
		} else {
			leaf->right = new Node<T>();
			leaf->right->value = key;
			leaf->right->right = nullptr;
			leaf->right->left = nullptr;
		}
	}
}

template <class T>
void BinaryTree<T>::insert(T key) 
{
	if (root != nullptr) {
		insert(key, root);
	} else {
		this->root = new Node<T>(key);
	}
}

// Recursive
template <class T>
Node<T>* BinaryTree<T>::search(T key, Node<T>* leaf) 
{
	if (leaf == nullptr) {
		return leaf;
	} else if (key == leaf->value) {
		return leaf;
	} else {
		return (key < leaf->value) ? search(key, leaf->left) : search(key, leaf->right);
	}
}

template <class T>
Node<T>* BinaryTree<T>::search(T key) 
{
	return search(key, root);
}

int main() 
{
	BinaryTree<int> binaryTree;

	binaryTree.insert(10);
	binaryTree.insert(9);
	binaryTree.insert(8);
	binaryTree.insert(7);
	binaryTree.insert(6);
	binaryTree.insert(5);
	binaryTree.insert(4);
	binaryTree.insert(3);
	binaryTree.insert(2);
	binaryTree.insert(1);

	Node<int>* getNode = binaryTree.search(5);

	std::cout << getNode->value << std::endl;

	return 0;
}