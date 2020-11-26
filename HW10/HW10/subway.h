#ifndef SUBWAY_H
#define	SUBWAY_H
#include <iostream>
using namespace std;

class Node {
	int lineNum;
	string lineName;
public:
	Node(int num = 0, string name = "no_staiton") : lineNum(num), lineName(name) {}
	int getLineNum() { return lineNum; }
	string getLineName() { return lineName; }
};

class Graph {
	int** weight; //이차원 배열 동적할당을 위한 이중포인터.
	Node* vertex;
	int* path;
	int capacity;
	int vertexNum;
public:
	Graph() { capacity = 1; vertexNum = 0; weight = 0; }
	void makeGraph(istream& is, int& numLine);
	void changeSize(int size);
	int search(int num, string name);
	void shortestPath(int, int);
	void searchPath(int, string, int, string);
	int getWeight(int m, int n) { return weight[m][n]; }
	friend ostream& operator <<(ostream& os, Node n);
};


#endif