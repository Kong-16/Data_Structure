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
void insertionSort(T* arr, int n) { // arr[1:n] 삽입정렬
	for (int i = 2; i <= n; i++) {
		T temp = arr[i]; // 삽입할 데이터
		int j = i - 1;
		while (arr[j] > temp && j > 0) { // temp보다 작은 데이터가 나올 때 까지
			arr[j + 1] = arr[j]; // 이전의 데이터를 한 칸씩 옮김
			j--;
		}
		arr[j + 1] = temp;
	}
}

template <class T>
void quickSort(T* arr, int left, int right) { //arr[left:right] 퀵정렬
	if (left < right) { // right가 left보다 작으면 종료.
		T pivot = arr[left];
		int i = left + 1; int j = right;
		while (i < j) { // i와 j가 엇갈리면 종료.
			while (arr[i] <= pivot && i < right + 1) i++;
			while (arr[j] > pivot && j > left) j--;
			if (i < j) swap(arr[i], arr[j]);
		} // while종료시 arr[j]는 가장 오른쪽에 위치한 pivot보다 작은 값. 
		swap(arr[left], arr[j]);//따라서 arr[j]와 pivot의 위치인 arr[left] 바꿔주면 arr[left]가 제자리로 감.
		quickSort(arr, left, j - 1);
		quickSort(arr, j + 1, right);
	}
}

template <class T>
void merge(T* initArr, T* mergedArr, int l, int m, int n) {//initArr[l:m], initArr[m+1:n]을 정렬해 mergedArr[l:n]에 저장.
	int i1, iResult, i2;
	i1 = iResult = l;
	i2 = m + 1;

	while (i1 <= m && i2 <= n) { //두 배열 비교해 작은 값 부터 순서대로 저장.
		if (initArr[i1] < initArr[i2]) mergedArr[iResult++] = initArr[i1++]; 
		else mergedArr[iResult++] = initArr[i2++]; 
	}
	
	copy(initArr + i1, initArr + m + 1, mergedArr + iResult); //m과 n의 길이가 다를 경우 한 쪽이 먼저 끝남. 나머지 값 삽입.
	copy(initArr + i2, initArr + n + 1, mergedArr + iResult);
}

template <class T>
void mergePass(T* initArr, T* resultArr, int n, int s) { // s개 단위로 정렬된 배열을 2s개 단위로 정렬된 배열로 만들어 resultArr에 저장.
	int i;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) merge(initArr, resultArr, i, i + s - 1, i + 2 * s - 1);
	if ((i + s - 1) < n) merge(initArr, resultArr, i, i + s - 1, n);
	else copy(initArr + i, initArr + n + 1, resultArr + i);

}

template <class T>
void mergeSort(T* arr, int n) { //arr[1:n] 합병정렬
	T* tempArr = new T[n + 1];
	for (int l = 1; l < n; l *= 2) {
		mergePass(arr, tempArr, n, l);
		l *= 2;
		mergePass(tempArr, arr, n, l);
	}
	delete[] tempArr;
}

template <class T>
void recursiveMerge(T* arr, T* tempArr, int left, int right) {//arr[left:right] 재귀합병정렬
	if (left >= right) return;
	int mid = (left + right) / 2; // 배열의 절반
	recursiveMerge(arr,tempArr, left, mid);
	recursiveMerge(arr,tempArr, mid + 1, right); //각 절반을 매개변수로 재귀적 호출 -> 절반씩 쪼개짐
	merge(arr, tempArr, left, mid, right); //다 쪼개질 경우 merge로 합쳐서 tempArr에 저장
	copy(tempArr + left, tempArr + right + 1, arr + left);// 정리된 배열 arr에 다시 넣음. 다음 합병을 위함.
}

template <class T>
void rmergeSort(T* arr, int n) { //
	T* tempArr = new T[n + 1];
	recursiveMerge(arr, tempArr, 1, n);
	copy(tempArr, tempArr + n, arr);
	delete[] tempArr;
}

template <class T>
void nmergeSort(T* arr, int n) { //arr[1:n] 자연합병정렬
	T* tempArr = new T[n + 1];
	int heapSize = 1;
	int i;
	int* incIndex = new int[n + 1]; //arr의 index담을 배열.
	incIndex[0] = 0; // 시작 값 0
	for (i = 1; i < n; i++) 
		if (arr[i] > arr[i + 1])  incIndex[heapSize++] = i; // 배열이 오름차순인 마지막 i값 incIndex에 저장.
	incIndex[heapSize] = n; // 끝 값 n
	// arr[incIndex[i-1]+1 : incIndex[i]]는 정렬돼있는 리스트. 
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
void heapSort(T* a, int n) {//arr[1:n] 힙정렬
	for (int i = n / 2; i >= 1; i--) adjust(a, i, n);
	for (int i = n - 1; i >= 1; i--) {
		swap(a[1], a[i + 1]);
		adjust(a, 1, i);
	}
}

#endif