#include "matrixa.h"
Matrix::Matrix(int a, int b, int c, int d) { 
	m[0][0] = a;
	m[0][1] = b;
	m[1][0] = c;
	m[1][1] = d;
}

void Matrix::Transpose() { //b와 d 값 바꿈.
	swap(m[0][1], m[1][0]);
}

Matrix Matrix::operator+(const Matrix& a) {// 각 원소 더한 값 리턴.
	Matrix c;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			c.m[i][j] = m[i][j] + a.m[i][j];
		}
	}
	return c;
}

Matrix Matrix::operator-(const Matrix& a) {
	Matrix c;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			c.m[i][j] = m[i][j] - a.m[i][j];
		}
	}
	return c;
}

Matrix Matrix::operator*(const Matrix& a) {
	Matrix c;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			c.m[i][j] = m[i][0] * a.m[0][j] + m[i][1] * a.m[1][j];
		}
	}
	return c;
}

void Matrix::operator=(const Matrix& a) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			m[i][j] = a.m[i][j];
		}
	}
}

void Matrix::ShowMatrix() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
}
int Matrix::GetDet() { // ad-bc 리턴.
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}