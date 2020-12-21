#ifndef GENLIST_H
#define GENLIST_H
using namespace std;
class GenList;
class GenListNode { //���븮��Ʈ ���
	friend class GenList;
public:
	GenListNode(bool t = false, GenListNode* n = NULL) : tag(t), next(n), data(0) {}
private:
	GenListNode* next;
	bool tag;
	union {
		char data;
		GenListNode* down;
	};
};
class GenList {
public:
	GenList() { first = NULL; }
	void Make() {//Make driver
		char a;
		cin >> a;//ù ( �� ����
		Make(first);
	}
	void Print() {//Print driver
		cout << "(";
		Print(first);
		cout << endl;
	}
	void Insert(char i, char j) {//Insert driver
		Insert(first, i, j);
	}
	void Delete(char i) {//Delete driver
		Delete(first, i);
	}
private:
	GenListNode* first;
	void Make(GenListNode*&);
	void Print(GenListNode*&);
	void Insert(GenListNode*&, char, char);
	void Delete(GenListNode*&, char);
};
#endif