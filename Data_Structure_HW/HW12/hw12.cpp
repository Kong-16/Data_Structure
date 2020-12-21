#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/time.h>
#include "sort.h"
using namespace std;

int main(int argc, char* argv[]) {
	int T = atoi(argv[1]); // num of test case
	cout << "T=" << T << endl;
	int N; // 각 테스트케이스 별 레코드의 길이
	int i; // iterator
	double result[6]; // result 배열에 각 알고리즘 별로 실행시간을 저장하게 됩니다.
	// result[0]: insertion sort
	// result[1]: quick 
	// result[2]: iterative merge sort
	// result[3]: reculsive merge sort
	// result[4]: natural merege sort
	// result[5]: heap sort
	struct timeval start_t, end_t;
	double diff_t;
	if (argc < 3) {
		cerr << "wrong argument count" << endl;
		return 1;
	}

	cout << "--INS--|-QUICK-|-MERGE-|-RECMG-|-NATMG-|-HEAP--| " << endl;
	for (i = 2; i < T + 2; i++) {
		// i번째 인자의 파일을 읽습니다.
		ifstream fin(argv[i]);
		fin >> N;
		int* insert = new int[N + 1];
		int* quick = new int[N + 1];
		int* merge = new int[N + 1];
		int* recmg = new int[N + 1];
		int* natmg = new int[N + 1];
		int* heap = new int[N + 1];

		getdata(fin,insert,N);
		
		copy(insert, insert + N + 1, quick);
		copy(insert, insert + N + 1, merge);
		copy(insert, insert + N + 1, recmg);
		copy(insert, insert + N + 1, natmg);
		copy(insert, insert + N + 1, heap);


		// 각 정렬 알고리즘에 필요한 자료구조를 생성하고 데이터를 담습니다.
		// 여기부터 정렬 시간 측정을 시작합니다.

		gettimeofday(&start_t, NULL);
		insertionSort(insert, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[0] = diff_t;

		gettimeofday(&start_t, NULL);
		quickSort(quick, 1, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[1] = diff_t;

		gettimeofday(&start_t, NULL);
		mergeSort(merge, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[2] = diff_t;

		gettimeofday(&start_t, NULL);
		rmergeSort(recmg, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[3] = diff_t;

		gettimeofday(&start_t, NULL);
		nmergeSort(natmg, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[4] = diff_t;

		gettimeofday(&start_t, NULL);
		heapSort(heap, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[5] = diff_t;

		// 결과를 출력합니다. (이 부분은 수정하지 않습니다)
		cout.precision(5);
		cout << fixed;
		for (int j = 0; j < 6; j++) {
			cout << result[j] << "|";
		}
		cout << "N=" << N << endl;
	}
}