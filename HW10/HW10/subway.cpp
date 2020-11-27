#include <algorithm>
#include "subway.h"
int MAX_LENGTH;

ostream& operator <<(ostream& os, Node n) {
	os << n.getLineName() << endl;
	return os;
}

void Minheap::ChangeSize1D(int size) {//heap의 크기를 size만큼 늘리는 함수.
	capacity = size;
	Data* temp = new Data[capacity + 1];
//	copy(heap, heap + heapSize, temp);
	for (int i = 0; i < heapSize; i++) {
		temp[i] = heap[i];
	}
	heap = temp;
}

void Minheap::Push(const Data& newdata) {
	if (heapSize == capacity) ChangeSize1D(capacity * 2);
	heapSize++;
	int current = heapSize;
	while (current != 1 && newdata.value < heap[current / 2].value) {
		heap[current] = heap[current / 2];
		current = current / 2;
	}
	heap[current] = newdata;
}
void Minheap::Pop() {
	if (heapSize == 0) throw "Heap is empty";
	heap[1].~Data();
	Data last = heap[heapSize--];
	int current = 1;
	int child = 2;
	while (child <= heapSize) {
		if (child < heapSize && heap[child + 1].value < heap[child].value) child++;
		if (last.value <= heap[child].value) break;
		heap[current] = heap[child];
		current = child;
		child = child * 2;
	}
	heap[current] = last;
}
/*ostream& operator <<(ostream& os, Minheap& H)
{
	os << "<Heap contents> ";
	int i;
	for (i = 1; i <= H.heapSize; i++)
		os << i << ":" << H.heap[i].value << " ";
	os << endl;
}*/
Minheap :: Minheap(int _capacity) : capacity(10), heapSize(0)
{
	if (_capacity < 1)
		throw " Must be > 0";
	capacity = _capacity;
	heap = new Data[capacity + 1];
}

void Graph::changeSize(int size) {
	capacity = size;
	Node* tmpN = new Node[capacity + 1];
	int** tmpI = new int* [size];
	for (int i = 0; i < size; i++) {
		tmpI[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmpI[i][j] = MAX_LENGTH;
		}
	}
	for (int i = 0; i < vertexNum; i++) {
		tmpN[i] = vertex[i];
	}
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			tmpI[i][j] = weight[i][j];
		}
	}
	vertex = tmpN;
	weight = tmpI;
}

int Graph::search(int num, string name) { //같은 역이 있는지 찾아서 있으면 배열에 저장
	if (capacity == vertexNum) changeSize(capacity * 2);
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
	MAX_LENGTH = numLine;
	weight = new int*[1];
	weight[0] = new int[1];
	vertex = new Node;
	for (int i = 0; i < numLine; i++) {
		is >> lineNum >> lineName;
		m = search(lineNum, lineName);
		is >> lineNum >> lineName;
		n = search(lineNum, lineName);
		if (vertex[m].getLineName() == vertex[n].getLineName()) { //역 이름이 같은경우 환승
			weight[m][n] = weight[n][m] = 10; // 환승은 가중치 10
		}
		else {
			weight[m][n] = weight[n][m] = 20; //일반은 20
		}
	}
	path = new int[vertexNum];
	dist = new int[vertexNum];
}

void Graph::shortestPath(int m, int n) {
/*	for (int k = 0; k < vertexNum; k++)
		for (int i = 0; i < vertexNum; i++)
			for (int j = 0; j < vertexNum; j++)
				if ((weight[i][k] + weight[k][j]) < weight[i][j]) {
					weight[i][j] = weight[i][k] + weight[k][j];
					if (i == m) {
						cout << vertex[k];
						path[i] = k;
					}
				}*/
	Minheap h(10);
	bool* visit = new bool[vertexNum];
	for (int i = 0; i < vertexNum; i++) { visit[i] = false; dist[i] = weight[i][m]; }
	visit[m] = true;
	dist[m] = 0;
	for (int i = 0; i < vertexNum; i++) { // 가장 작은값 꺼내기 위해 최소힙 사용. 힙안에는 인덱스와 value를 저장하는 Data가 들어감.
		Data* newData = new Data;
		newData->num = i;
		newData->value = dist[i];
		h.Push(*newData);
	}
	h.Pop();
	while (!h.IsEmpty()) {
		cout << h.Top().num << endl;
		h.Pop();
	}
	for (int i = 0; i < vertexNum - 2; i++) {
		if (h.IsEmpty()) return;
		int u = h.Top().num;
		visit[u] = true;
		for (int w = 0; w < vertexNum; w++) {
			if (!visit[w] && dist[u] + weight[u][w] < dist[w]) {// u를 경유해서 가는것이 가중치가 적을 경우
				dist[w] = dist[u] + weight[u][w];
				path[w] = u; //path에 w로 가는 최단경로의 이전vertex u저장.
				if (w == n) return; // n까지 가는 최단경로 찾으면 종료.	
			}
		}
		h.Pop();
	}
}

void Graph::searchPath(int line1, string src, int line2, string dst) {
	int m, n, time, minute, second, half, min;
	m = search(line1, src);
	n = search(line2, dst);
	shortestPath(m, n);
	time = dist[n];
	minute = time / 20;
	second = (time % 20) * 3;
	min = time;
	cout << minute << ':' << second;
	while (n == m) {
		cout << vertex[n].getLineName();
		n = path[n];
		if (time - dist[n] < min) {
			min = time - dist[n];
			half = n;
		}
	}
	time = dist[n];
	minute = time / 20;
	second = (time % 20) * 3;
/*
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
	cout << minute << ':' << second;*/
}
