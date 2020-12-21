#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

class nodeptr {
	int data;
	int height;
	nodeptr* left;
	nodeptr* right;
	friend class bstree;
public:
	nodeptr() : data(NULL), left(NULL), right(NULL), height(0) {}
	nodeptr(int data) : data(data), left(NULL), right(NULL), height(1) {}
	bool operator != (const int& n) { return data != n;}
	friend ostream& operator <<(ostream& os, nodeptr*& node);
};

class bstree {
	nodeptr* root;
	nodeptr* balance(nodeptr*& node);
	nodeptr* LLrotate(nodeptr*& node);
	nodeptr* LRrotate(nodeptr*& node);
	nodeptr* RRrotate(nodeptr*& node);
	nodeptr* RLrotate(nodeptr*& node);
	int height(nodeptr*&);
	int getdiff(nodeptr*& node) { return height(node->left) - height(node->right); }
public:
	bstree() { root = NULL; }
	nodeptr* insert(int data, nodeptr*& root);
	void Search(int data, nodeptr*& root);
	void Showresult(nodeptr*& root);
	nodeptr* del(int data, nodeptr*& root);
};

ostream& operator <<(ostream& os, nodeptr*& node) {
	os << node->data;
	if (node->left != NULL) os << "\tleft : " << node->left->data;
	else os << "\tleft : empty";
	if (node->right != NULL) os << "\tright : " << node->right->data;
	else os << "\tright : empty";
	os << endl;
	return os;
}

void bstree::Search(int data, nodeptr*& node) {
	if (node == NULL) {
		cout << "can't find!" << endl;
		return;
	}
	if (data == node->data) cout << node->data << endl;
	else cout << node->data << " -> ";
	if (node->data < data) 
		Search(data, node->right);
	
	else if (node->data > data) 
		Search(data, node->left);

	return;
}

void bstree::Showresult(nodeptr*& node) {
	queue<nodeptr*> q;
	nodeptr* temp = node;
	while (temp) {
		cout << temp;
		if (temp->left)
			q.push(temp->left);
		if (temp->right)
			q.push(temp->right);
		if (q.empty()) return;
		temp = q.front();
		q.pop();
	}
}


nodeptr* bstree :: insert(int data, nodeptr*& node) {
	if (node == NULL)
		node = new nodeptr(data);
	else if (node->data < data)
		node->right = insert(data, node->right);
	else 
		node->left = insert(data, node->left);
	node->height = height(node);
	node = balance(node);
	
	return node;
}

int bstree :: height(nodeptr*& node) {
	if (node == NULL)
		return 0;
	return max(height(node->left), height(node->right)) + 1;
}

nodeptr* bstree :: balance(nodeptr*& node) {
	int diff = getdiff(node);
	if (diff > 1) { // L상태
		if (getdiff(node->left) > 0) // LL
			node = LLrotate(node);
		else // LR
			node = LRrotate(node);
	}
	else if (diff < -1) {
		if (getdiff(node->right) < 0) // RR
			node = RRrotate(node);
		else // RL
			node = RLrotate(node);
	}
	return node;
}

nodeptr* bstree :: LLrotate(nodeptr*& node) {
	nodeptr* temp = node->left;
	node->left = temp->right;
	temp->right = node;
	//높이조정
	temp->height = height(temp);
	node->height = height(node);
	return temp;
}

nodeptr* bstree :: LRrotate(nodeptr*& node) {
	node->left = RRrotate(node->left);
	node = LLrotate(node);
	return node->left;
}

nodeptr* bstree :: RRrotate(nodeptr*& node) {
	nodeptr* temp = node->right;
	node->right = temp->left;
	temp->left = node;
	//높이조정
	temp->height = height(temp);
	node->height = height(node);
	return temp;
}

nodeptr* bstree :: RLrotate(nodeptr*& node) {
	node->right = LLrotate(node->right);
	node = RRrotate(node);
	return node->right;
}

nodeptr* bstree:: del(int data, nodeptr*& node) {
	if (node == NULL) return node;

	if (node->data < data) {
		node->right = del(data, node->right);
	}
	else if (node->data > data) {
		node->left = del(data, node->left);
	}
	//삭제할 데이터 찾은 경우
	else {
		//자식이 없는 경우
		if (node->left == NULL && node->right == NULL) { 
			delete node;
			return NULL;
		}
		//자식이 하나인 경우
		if (node->left == NULL) { 
			nodeptr* temp = node->right;
			delete node;
			return temp;
		}
		if (node->right == NULL) {
			nodeptr* temp = node->left;
			delete node;
			return temp;
		}
		//자식이 둘인 경우
		//왼쪽 자식의 가장 오른쪽에 있는 노드와 교체.
		nodeptr* temp = node->left;
		if (temp->right == NULL) {
			delete node;
			return temp;
		}
		else {
			nodeptr* temp2 = node;
			nodeptr* temp3 = NULL;
			while (temp->right != NULL) {
				temp3 = temp;
				temp = temp->right;
			}
			if (temp->left != NULL) {
				temp3->right = temp->left;
			}
			temp->left = temp2->left;
			temp->right = temp2->right;
			temp2 = temp;
			delete node;
			return temp;
		}
	}
	node = balance(node);
	node->height = height(node);
	return node;
}
#endif