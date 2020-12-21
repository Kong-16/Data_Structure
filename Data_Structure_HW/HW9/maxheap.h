#ifndef __MAXHEAP_H__
#define __MAXHEAP_H__
#include<iostream>
#include<algorithm>
using namespace std;
template<class T>
class Maxheap {
private:
	void ChangeSize1D(int);
	T* heap;
	int heapSize;
	int capacity;
public:
	Maxheap(int);
	void Push(const T&);
	void Pop();
	bool IsEmpty() { return heapSize == 0; }
	T Top() { return heap[1]; }
	template<class T2> friend ostream& operator <<(ostream&, Maxheap<T2>&);
};
template<class T>
void Maxheap<T>::ChangeSize1D(int size) {//heap의 크기를 size만큼 늘리는 함수.
	capacity = size;
	T* temp = new T[capacity + 1];
	copy(heap, heap + heapSize, temp);
}
template <class T>
void Maxheap<T>::Push(const T& newdata) {
	if (heapSize == capacity) ChangeSize1D(capacity * 2);
	heapSize++;
	int current = heapSize;
	while (current != 1 && newdata > heap[current / 2]) {
		heap[current] = heap[current / 2];
		current = current / 2;
	}
	heap[current] = newdata;
}
template <class T>
void Maxheap<T>::Pop() {
	if (heapSize == 0) throw "Heap is empty";
	heap[1].~T();
	T last = heap[heapSize--];
	int current = 1;
	int child = 2;
	while (child <= heapSize) {
		if (child < heapSize && heap[child] < heap[child + 1]) child++;
		if (last >= heap[child]) break;
		heap[current] = heap[child];
		current = child;
		child = child * 2;
	}
	heap[current] = last;
}
template<class T>
ostream& operator <<(ostream& os, Maxheap<T>& H)
{
	os << "<Heap contents> ";
	int i;
	for (i = 1; i <= H.heapSize; i++)
		os << i << ":" << H.heap[i] << " ";
	os << endl;
}
template<class T>
Maxheap<T>::Maxheap(int _capacity = 10) : heapSize(0)
{
	if (_capacity < 1)
		throw " Must be > 0";
	capacity = _capacity;
	heap = new T[capacity + 1];
}
#endif