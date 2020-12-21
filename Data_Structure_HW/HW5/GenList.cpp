#include <iostream>
#include "GenList.h"
using namespace std;

void GenList::Make(GenListNode*& cur) { 
	char i;
	cin >> i;
	if (i == ')') return; //���Ż�� ����
	else if (i == '(') {
		if (cur == first) first = new GenListNode;
		cur->tag = true;
		cur->next = new GenListNode;
		cur->down = new GenListNode;
		Make(cur->down); //down ���� ȣ���ؾ� ���� ��� ���� �̾���.
		Make(cur->next); //���� ��� ������ ������ ���� ��� ����.
	}
	else {
		if (cur == first) first = new GenListNode;
		cur->data = i;
		cur->next = new GenListNode;
		Make(cur->next);
	}

}
void GenList::Print(GenListNode*& cur) {
	if (cur->next == NULL) {
		cout << ')';
		return;
	}
	else if (cur->tag) { // �Ʒ���
		cout << '(';
		Print(cur->down);
		Print(cur->next);
	}
	else { //������
		cout << cur->data;
		Print(cur->next);
	}
}
void GenList::Insert(GenListNode*& cur, char i, char j) {
	if (cur == NULL) return;
	else if (cur->tag) {
		Insert(cur->down, i, j);
		Insert(cur->next, i, j);
	}
	else if (cur->data == i) {
		GenListNode* newNode = new GenListNode;
		newNode->next = cur->next;
		newNode->data = j;
		cur->next = newNode;
		Insert(newNode->next, i, j); // �� ���� �˻����� ����. //�˻� �� ��� insert(a,a) ���� �� �����߻�.
	}
	else Insert(cur->next, i, j);
}
void GenList::Delete(GenListNode*& cur, char i) {
	if (cur->next== NULL) return;
	if (cur == first) {
		if (cur->data == i) {
			GenListNode* h;
			h = first;
			first = first->next;
			delete h;
			Delete(first, i);
		}
	}
	if (cur->tag) {
		if (cur->down->data == i) {
			GenListNode* newNode;
			newNode = cur->down;
			cur->down = cur->down->next;
			delete newNode;
			Delete(cur, i); // aa�� ���� �پ��ִ� ��� ������ ���� cur�� �ٽ� ���.
		}
		else Delete(cur->down, i);

		if (cur->next->data == i) {
			GenListNode* newNode;
			newNode = cur->next;
			cur->next = cur->next->next;
			delete newNode;
			Delete(cur, i);
		}
		else Delete(cur->next, i);
	}
	else if (cur->next->data == i) {
		GenListNode* newNode;
		newNode = cur->next;
		cur->next = cur->next->next;
		delete newNode;
		Delete(cur, i);
	}
	else Delete(cur->next, i);
}