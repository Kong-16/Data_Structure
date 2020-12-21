#include <iostream>
#include <string>
using namespace std;
template <class K, class E>
struct Node {
	Node(K ky, E el, Node<K, E>* left = 0, Node<K, E>* right = 0,bool leftT = true, bool rightT = true) : key(ky), element(el), leftChild(left), rightChild(right), leftThread(leftT), rightThread(rightT){}
	Node<K, E>* leftChild;
	K key;
	E element;
	Node<K, E>* rightChild;
	bool leftThread; //thread로 이어져있는지 확인함. true면 thread, false면 child Node.
	bool rightThread;
}; 
template <class K, class E>
class BST {
public:
	BST() { root = 0; }
	void Insert(K& newkey, E& el) { Insert(root, newkey, el); }
	void Inorder() { Inorder(root); }
	void Delete(K& oldkey) { Delete(root, root, oldkey); }
	bool Find(const K&, E&);
	void Max() { cout << "maximum value is " << Max(root)->key << ':' << Max(root)->element << endl; }
	void Min() { cout << "minimum value is " << Min(root)->key << ':' << Min(root)->element << endl; }
private:
	void Visit(Node<K, E>*);
	void Insert(Node<K, E>*&, K&, E&); // 구현
	void Inorder(Node<K, E>*);
	void Delete(Node<K, E>*&, Node<K, E>*&, K&); // 구현
	Node<K, E>* Max(Node<K, E>*&); // 구현
	Node<K, E>* Min(Node<K, E>*&); // 구현
	Node<K, E>* root;
};
template <class K, class E>
void BST<K, E>::Insert(Node<K, E>*& n, K& k, E& el) {
	Node<K, E>* newNode = new Node<K, E>(k,el);
	Node<K, E>* temp = root;
	if (root == 0) {// 루트가 없을 시 루트에 넣고 스레드 본인에게 이어줌.
		root = newNode;
		newNode->rightChild = newNode;
		newNode->leftChild = newNode;
		return;
	}
	while (temp) {
		if (k > temp->key) {
			if (temp->rightThread == true) { // Thread일 경우 부모의 thread를 이어주고 부모 false로 바꿈. 이후 노드 연결후 자식노드 왼쪽스레드 이어줌
				newNode->rightChild = temp->rightChild;
				temp->rightThread = false;
				temp->rightChild = newNode;
				newNode->leftChild = temp;
				return;
			}
			temp = temp->rightChild;
		}
		else if (k < temp->key) {
			
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
			temp->element = el;
				return;
		}
	}
}
template <class K, class E>
void BST<K, E>::Visit(Node<K, E>* ptr) {
	cout << ptr->key << ':' << ptr->element << ' ';
}
template <class K, class E>
void BST<K, E>::Inorder(Node<K, E>* currentNode) {
		if(currentNode->leftThread == false) Inorder(currentNode->leftChild);
		Visit(currentNode);
		if(currentNode->rightThread == false)Inorder(currentNode->rightChild);
}
template <class K, class E>
bool BST<K, E>::Find(const K& k, E& e) {
	Node<K, E>* temp = root;
	while (temp) {
		if (k > temp->key) {
			if (temp->rightThread == false) temp = temp->rightChild;
			else return false;
		}
		else if (k < temp->key) {
			if (temp->leftThread == false) temp = temp->leftChild;
			else return false;
		}
		else {
			e = temp->element;
			return true;
		}
	}
}
template <class K, class E>
void BST<K, E> :: Delete(Node<K, E>*& r, Node<K, E>*& n, K& k) {
	Node<K, E>* temp = r;
	Node<K, E>* pre = 0;
	Node<K, E>* par = 0;
	while (true) {
		if (k > temp->key) {
			if (temp->rightThread == true) { 
				cout << "No such key"; 
				return;
			}
			pre = temp;
			temp = temp->rightChild;
		}
		else if (k < temp->key) {
			if (temp->leftThread == true) {
				cout << "No such key";
				return;
			}
			pre = temp;
			temp = temp->leftChild;
		}
		else { //삭제할 노드 발견한 경우
			if (temp->leftThread == true) { 
				if (temp->rightThread == true) { //자식 노드가 없을 때
					if (temp == pre->leftChild) {
						pre->leftChild = temp->leftChild;
						pre->leftThread = true;
						delete temp;
						return;
					}
					else {
						pre->rightChild = temp->rightChild;
						pre->rightThread = true;
						delete temp;
						return;
					}
				} 
				else {  //오른쪽 자식 노드만 있을 때
					if (temp == pre->leftChild) {
						pre->leftChild = temp->rightChild;
						pre->leftChild->leftThread = temp->leftThread;
						pre->leftChild->leftChild = temp->leftChild;
					}
					else {
						pre->rightChild = temp->rightChild;
						pre->rightChild->leftThread = temp->leftThread;
						pre->rightChild->leftChild = temp->leftChild;
					}
					delete temp;
					return;
				}
			}
			else {//삭제할 노드의 왼쪽 자식 있음.
				pre = temp;
				temp = temp->leftChild;
				if (temp->rightThread == true) { // 삭제할 노드가 왼쪽 자식만 있을 때
					pre->key = temp->key;
					pre->element = temp->element;
					pre->leftChild = temp->leftChild;
					pre->leftThread = temp->leftThread;
				}
				else { // 삭제할 노드의 왼쪽 자식의 오른쪽 자식이 있을 때
					while (temp->rightThread == true) { //오른쪽 끝까지감
						par = temp;
						temp = temp->rightChild;
					}
					pre->key = temp->key;
					pre->element = temp->element; //복사
					if (temp->leftThread == true) { //대체할 노드의 자식이 없을 때
						par->rightChild = temp->rightChild;
						par->rightThread = true;
					}
					else {
						par->rightChild = temp->leftChild;
					}
				}
				delete temp;
				return;
			}
		}
	}
}
template <class K, class E>
Node<K, E>* BST<K, E>:: Max(Node<K, E>*& n) {
	Node<K, E>* temp = n;
	while (temp->rightThread == false)
		temp = temp->rightChild;
	return temp;
}
template <class K, class E>
Node<K, E>* BST<K, E>::Min(Node<K, E>*& n) {
	Node<K, E>* temp = root;
	while (temp->leftThread == false)
		temp = temp->leftChild;
	return temp;
}

