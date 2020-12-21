#include <iostream>
#include <fstream>
#include <ctime>
#include "sort.h"
using namespace std;

int main() {
	//	int T = atoi(argv[1]); // num of test case
	//	cout << "T=" << T << endl;
	int N; // �� �׽�Ʈ���̽� �� ���ڵ��� ����
	int i; // iterator
	clock_t result[6]; // result �迭�� �� �˰��� ���� ����ð��� �����ϰ� �˴ϴ�.
	// result[0]: insertion sort
	// result[1]: quick 
	// result[2]: iterative merge sort
	// result[3]: reculsive merge sort
	// result[4]: natural merege sort
	// result[5]: heap sort
	clock_t start;
	clock_t end;
	//	if (argc < 3) {
	//		cerr << "wrong argument count" << endl;
	//		return 1;
	//	}


	//	for (i = 2; i < T + 2; i++) {
			// i��° ������ ������ �н��ϴ�.
	ifstream fin("input.txt");
	fin >> N;
	int* insert = new int[N + 1];
	int* quick = new int[N + 1];
	int* merge = new int[N + 1];
	int* recmg = new int[N + 1];
	int* natmg = new int[N + 1];
	int* heap = new int[N + 1];

	getdata(fin, insert, N);

	copy(insert, insert + N + 1, quick);
	copy(insert, insert + N + 1, merge);
	copy(insert, insert + N + 1, recmg);
	copy(insert, insert + N + 1, natmg);
	copy(insert, insert + N + 1, heap);


	// �� ���� �˰��� �ʿ��� �ڷᱸ���� �����ϰ� �����͸� ����ϴ�.
	// ������� ���� �ð� ������ �����մϴ�.

	start = clock();
	insertionSort(insert, N);
	end = clock();
	result[0] = end - start;

	start = clock();
	quickSort(quick, 1, N);
	end = clock();
	result[1] = end - start;

	start = clock();
	mergeSort(merge, N);
	end = clock();
	result[2] = end - start;

	start = clock();
	rmergeSort(recmg, N);
	end = clock();
	result[3] = end - start;

	start = clock();
	nmergeSort(natmg, N);
	end = clock();
	result[4] = end - start;

	start = clock();
	heapSort(heap, N);
	end = clock();
	result[5] = end - start;
	cout << endl;
	cout << "--INS--|-QUICK-|-MERGE-|-RECMG-|-NATMG-|-HEAP--| " << endl;
	// ����� ����մϴ�. (�� �κ��� �������� �ʽ��ϴ�)
	cout.precision(5);
	cout << fixed;
	for (int j = 0; j < 6; j++) {
		cout << (double)result[j] / CLOCKS_PER_SEC << "|";
	}
	cout << "N=" << N << endl;

	delete[] insert;
	delete[] quick;
	delete[] merge;
	delete[] recmg;
	delete[] natmg;
	delete[] heap;
	
}
//}