#ifndef Sort_H__
#define Sort_H__
#include <algorithm>
using namespace std;

template <class T>
void getdata(istream& is, T* arr, int n) {
	T data;
	for (int i = 1; i <= n; i++) {
		is >> data;
		arr[i] = data;
	}
}

template <class T>
void insertionSort(T* arr, int n) { // arr[1:n] ��������
	for (int i = 2; i <= n; i++) {
		T temp = arr[i]; // ������ ������
		int j = i - 1;
		while (arr[j] > temp && j > 0) { // temp���� ���� �����Ͱ� ���� �� ����
			arr[j + 1] = arr[j]; // ������ �����͸� �� ĭ�� �ű�
			j--;
		}
		arr[j + 1] = temp;
	}
}

template <class T>
void quickSort(T* arr, int left, int right) { //arr[left:right] ������
	if (left < right) { // right�� left���� ������ ����.
		T pivot = arr[left];
		int i = left + 1; int j = right;
		while (i < j) { // i�� j�� �������� ����.
			while (arr[i] <= pivot && i < right + 1) i++;
			while (arr[j] > pivot && j > left) j--;
			if (i < j) swap(arr[i], arr[j]);
		} // while����� arr[j]�� ���� �����ʿ� ��ġ�� pivot���� ���� ��. 
		swap(arr[left], arr[j]);//���� arr[j]�� pivot�� ��ġ�� arr[left] �ٲ��ָ� arr[left]�� ���ڸ��� ��.
		quickSort(arr, left, j - 1);
		quickSort(arr, j + 1, right);
	}
}

template <class T>
void merge(T* initArr, T* mergedArr, int l, int m, int n) {//initArr[l:m], initArr[m+1:n]�� ������ mergedArr[l:n]�� ����.
	int i1, iResult, i2;
	i1 = iResult = l;
	i2 = m + 1;

	while (i1 <= m && i2 <= n) { //�� �迭 ���� ���� �� ���� ������� ����.
		if (initArr[i1] < initArr[i2]) mergedArr[iResult++] = initArr[i1++]; 
		else mergedArr[iResult++] = initArr[i2++]; 
	}
	
	copy(initArr + i1, initArr + m + 1, mergedArr + iResult); //m�� n�� ���̰� �ٸ� ��� �� ���� ���� ����. ������ �� ����.
	copy(initArr + i2, initArr + n + 1, mergedArr + iResult);
}

template <class T>
void mergePass(T* initArr, T* resultArr, int n, int s) { // s�� ������ ���ĵ� �迭�� 2s�� ������ ���ĵ� �迭�� ����� resultArr�� ����.
	int i;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) merge(initArr, resultArr, i, i + s - 1, i + 2 * s - 1);
	if ((i + s - 1) < n) merge(initArr, resultArr, i, i + s - 1, n);
	else copy(initArr + i, initArr + n + 1, resultArr + i);

}

template <class T>
void mergeSort(T* arr, int n) { //arr[1:n] �պ�����
	T* tempArr = new T[n + 1];
	for (int l = 1; l < n; l *= 2) {
		mergePass(arr, tempArr, n, l);
		l *= 2;
		mergePass(tempArr, arr, n, l);
	}
	delete[] tempArr;
}

template <class T>
void recursiveMerge(T* arr, T* tempArr, int left, int right) {//arr[left:right] ����պ�����
	if (left >= right) return;
	int mid = (left + right) / 2; // �迭�� ����
	recursiveMerge(arr,tempArr, left, mid);
	recursiveMerge(arr,tempArr, mid + 1, right); //�� ������ �Ű������� ����� ȣ�� -> ���ݾ� �ɰ���
	merge(arr, tempArr, left, mid, right); //�� �ɰ��� ��� merge�� ���ļ� tempArr�� ����
	copy(tempArr + left, tempArr + right + 1, arr + left);// ������ �迭 arr�� �ٽ� ����. ���� �պ��� ����.
}

template <class T>
void rmergeSort(T* arr, int n) { //
	T* tempArr = new T[n + 1];
	recursiveMerge(arr, tempArr, 1, n);
	copy(tempArr, tempArr + n, arr);
	delete[] tempArr;
}

template <class T>
void nmergeSort(T* arr, int n) { //arr[1:n] �ڿ��պ�����
	T* tempArr = new T[n + 1];
	int heapSize = 1;
	int i;
	int* incIndex = new int[n + 1]; //arr�� index���� �迭.
	incIndex[0] = 0; // ���� �� 0
	for (i = 1; i < n; i++) 
		if (arr[i] > arr[i + 1])  incIndex[heapSize++] = i; // �迭�� ���������� ������ i�� incIndex�� ����.
	incIndex[heapSize] = n; // �� �� n
	// arr[incIndex[i-1]+1 : incIndex[i]]�� ���ĵ��ִ� ����Ʈ. 
	while (heapSize > 1) {
		for (i = 0; i < heapSize; i += 2) {
			if (i == heapSize - 1) { 
				incIndex[(i / 2) + 1] = incIndex[i + 1];
			}
			else {
				merge(arr, tempArr, incIndex[i] + 1, incIndex[i + 1], incIndex[i + 2]);
				copy(tempArr + incIndex[i] + 1, tempArr + incIndex[i + 2] + 1, arr + incIndex[i] + 1);
				incIndex[(i / 2) + 1] = incIndex[i + 2];
			}
		}
		if (i == heapSize + 1) heapSize = (heapSize / 2) + 1;
		else heapSize = heapSize / 2;
	}
	delete[] tempArr;
}

template <class T>
void adjust(T* arr, int root, int n) {
	T e = arr[root];
	int j;
	for (j = 2 * root; j <= n; j *= 2) {
		if (j < n && arr[j] < arr[j + 1])j++;
		if (e >= arr[j])break;
		arr[j / 2] = arr[j];
	}
	arr[j / 2] = e;
}

template <class T>
void heapSort(T* a, int n) {//arr[1:n] ������
	for (int i = n / 2; i >= 1; i--) adjust(a, i, n);
	for (int i = n - 1; i >= 1; i--) {
		swap(a[1], a[i + 1]);
		adjust(a, 1, i);
	}
}

#endif