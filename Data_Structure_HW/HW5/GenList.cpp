#include <iostream>
#include "GenList.h"
using namespace std;

void GenList::Make(GenListNode*& cur) { 
	char i;
	cin >> i;
	if (i == ')') return; //재귀탈출 조건
	else if (i == '(') {
		if (cur == first) first = new GenListNode;
		cur->tag = true;
		cur->next = new GenListNode;
		cur->down = new GenListNode;
		Make(cur->down); //down 먼저 호출해야 세로 노드 먼저 이어줌.
		Make(cur->next); //세로 노드 연결이 끝나면 가로 노드 진행.
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
	else if (cur->tag) { // 아래로
		cout << '(';
		Print(cur->down);
		Print(cur->next);
	}
	else { //옆으로
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
		Insert(newNode->next, i, j); // 새 노드는 검사하지 않음. //검사 할 경우 insert(a,a) 실행 시 오류발생.
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
			Delete(cur, i); // aa와 같이 붙어있는 노드 삭제를 위해 cur을 다시 사용.
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