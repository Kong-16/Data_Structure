#include <algorithm>
#include "subway.h"


ostream& operator <<(ostream& os, Node n) {
	os << n.getLineName() << endl;
	return os;
}

void Graph::changeSize(int size) {
	capacity = size;
	Node* tmpN = new Node[capacity + 1];
	int** tmpI = new int* [size];
	for (int i = 0; i < size; i++) {
		tmpI[i] = new int[size];
	}
	for (int i = 0; i < vertexNum + 1; i++) {
		tmpN[i] = vertex[i];
	}
	for (int i = 0; i < vertexNum + 1; i++) {
		for (int j = 0; j < vertexNum + 1; j++) {
			tmpI[i][j] = weight[i][j];
		}
	}
	vertex = tmpN;
	weight = tmpI;
}

int Graph::search(int num, string name) { //같은 역이 있는지 찾아서 있으면 배열에 저장,
	for (int i = 0; i < vertexNum; i++) {
		if (vertex[i].getLineName() == name)
			if (vertex[i].getLineNum() == num)
				return i;
	}
	Node* n = new Node(num, name); // 없으면 노드생성 후 노드 저장된 배열의 인덱스 리턴.
	vertex[vertexNum] = *n;
	return vertexNum++;
}

void Graph::makeGraph(istream& is, int& numLine) { // 자료를 읽어 graph를 만든다.
	int lineNum, m, n;
	string lineName;
	weight = new int*[1];
	weight[0] = new int[1];
	vertex = new Node;
	for (int i = 0; i < numLine; i++) {
		if (capacity == vertexNum + 1) changeSize(capacity * 2);
		is >> lineNum >> lineName;
		m = search(lineNum, lineName);
		is >> lineNum >> lineName;
		n = search(lineNum, lineName);
		if (vertex[m].getLineName() == vertex[n].getLineName()) {
			weight[m][n] = weight[n][m] = 10; // 환승은 가중치 10
		}
		else {
			weight[m][n] = weight[n][m] = 20; //일반은 20
		}
	}
	path = new int[vertexNum];
}

void Graph::shortestPath(int m, int n) {
	for (int k = 0; k < vertexNum; k++)
		for (int i = 0; i < vertexNum; i++)
			for (int j = 0; j < vertexNum; j++)
				if ((weight[i][k] + weight[k][j]) < weight[i][j]) {
					weight[i][j] = weight[i][k] + weight[k][j];
					if (i == m) cout << vertex[m] << endl;
					path[i] = m;
				}

}

void Graph::searchPath(int line1, string src, int line2, string dst) {
	int m, n, time, minute, second, half, min, num;
	m = search(line1, src);
	n = search(line2, dst);
	shortestPath(m, n);
	time = getWeight(m, n);
	minute = time / 20;
	second = (time % 20) * 3;
	cout << minute << ':' << second;
	min = time;
	half = time / 2;
	for (int i = 0; i < vertexNum; i++) {
		if (half - weight[i][path[i]] < min) {
			min = half - weight[i][path[i]];
			num = i;
		}
	}
	cout << vertex[num] << endl;
	time = getWeight(m, path[num]);
	minute = time / 20;
	second = (time % 20) * 3;
	cout << minute << ':' << second;
	time = getWeight(n, path[num]);
	minute = time / 20;
	second = (time % 20) * 3;
	cout << minute << ':' << second;
}
