#include <iostream>
#include "GenList.h"
using namespace std;
int main() {
	GenList Inlist;
	Inlist.Make();//���븮��Ʈ ����
	Inlist.Print();//���븮��Ʈ ���
	while (1) {
		/*
		1 : Insert
		2 : Delete
		3 : Print4 : ����
		*/
		int select;
		cin >> select;
		char i, j;
		if (select == 1) {
			cin >> i >> j;
			Inlist.Insert(i, j);
		}
		else if (select == 2) {
			cin >> i;
			Inlist.Delete(i);
		}
		else if (select == 3) {
			Inlist.Print();
		}
		else if (select == 4) {
			break;
		}
		else {
			cout << "Wrong Command" << endl;
		}
	}
}