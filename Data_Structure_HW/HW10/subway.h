#ifndef SUBWAY_H
#define	SUBWAY_H
#include <iostream>
using namespace std;

class Node {
	Node* next;
	Node* prev;
	int lineNum;
	string lineName;
public:
	Node(int num = 0, Node* n = NULL) : lineNum(0), next(n), prev(n) {}
};

class Graph {
	Node* a;
};

#endif