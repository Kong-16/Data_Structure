#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <class T>
struct Node
{
	Node(T d, Node<T>* left = 0, Node<T>* right = 0, bool thread = true)
		: data(d), leftChild(left), rightChild(right),leftThread(thread), rightThread(thread) {}
	Node<T>* leftChild;
	bool leftThread;
	T data;
	Node<T>* rightChild;
	bool rightThread;
};
template <class T>
class Tree
{
public:
	Tree() { root = 0; } // empty tree
	void Insert(T& value) { Insert(root, value); }
	void Preorder() { Preorder(root); }
	void Inorder() { Inorder(root); }
	void Postorder() { Postorder(root); }
	void Levelorder();
private: // helper 함수들
	void Visit(Node<T>*);
	void Insert(Node<T>*&, T&);
	void Preorder(Node<T>*);
	void Inorder(Node<T>*);
	void Postorder(Node<T>*);
	Node<T> * root;
};
template <class T>
void Tree<T>::Visit(Node<T>* ptr) { cout << ptr->data << " "; }
template <class T>
void Tree<T>::Insert(Node<T>*& ptr, T& value)
{ //Insert 의 helper 함수
	Node<T>* newNode = new Node<T>(value);
	Node<T>* temp = root;
	if (root == 0) {// 루트가 없을 시 루트에 넣고 스레드 본인에게 이어줌.
		root = newNode;
		newNode->rightChild = newNode;
		newNode->leftChild = newNode;
		return;
	}
	while (temp) {
		if (value > temp->data) {
			if (temp->rightThread == true) { // Thread일 경우 부모의 thread를 이어주고 부모 false로 바꿈. 이후 노드 연결후 자식노드 왼쪽스레드 이어줌
				newNode->rightChild = temp->rightChild;
				temp->rightThread = false;
				temp->rightChild = newNode;
				newNode->leftChild = temp;
				return;
			}
			temp = temp->rightChild;
		}
		else if (value < temp->data) {
			if (temp->leftThread == true) {
				newNode->leftChild = temp->leftChild;
				temp->leftThread = false;
				temp->leftChild = newNode;
				newNode->rightChild = temp;
				return;
			}
			temp = temp->leftChild;
		}
		else {
			cout << "duplicate value" << value << "ignored";
			return;
		}
	}
}
template <class T>
void Tree<T>::Preorder(Node<T>* node) {
	Visit(node);
	if (node->leftThread == false) Preorder(node->leftChild);
	if (node->rightThread == false) Preorder(node->rightChild);
}
template <class T>
void Tree<T>::Inorder(Node<T>* node) {
	Node<T>* temp = node;
	stack<Node<T>*> stack;
	while (temp->leftThread == false) {
		temp = temp->leftChild;
	}
	while (temp != node) {
		Visit(temp);
		temp = temp->rightChild;
	}
	Visit(node);
	while (temp->rightThread == false) {
		temp = temp->rightChild;
	}
	while (temp != node) {
		stack.push(temp);
		temp = temp->leftChild;
	}
	while (!stack.empty()) {
		Visit(stack.top());
		stack.pop();
	}
}
template <class T>
void Tree<T>::Postorder(Node<T>* node) {
	if (node->leftThread == false) Postorder(node->leftChild);
	if (node->rightThread == false) Postorder(node->rightChild);
	Visit(node);
}

template <class T>
void Tree<T>::Levelorder() {
	queue<Node<T>*> q;
	Node<T>* temp = root;
	while (true) {
		Visit(temp);
		if (temp->leftThread == false) q.push(temp->leftChild);
		if (temp->rightThread == false) q.push(temp->rightChild);
		if (q.empty()) return;
		temp = q.front();
		q.pop();
	}
}

//Preorder, Inorder, Postorder 함수를 구현하시오......
//Levelorder(교재 p266 참조하되 STL 큐를 이용) 를 구현하시오.
#endif
