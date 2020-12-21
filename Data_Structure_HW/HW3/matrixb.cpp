#include "matrixb.h"
Matrix::Matrix(int a, int b, int c, int d,int e, int f, int g, int h, int i	) {
	m[0][0] = a;
	m[0][1] = b;
	m[0][2] = c;
	m[1][0] = d;
	m[1][1] = e;
	m[1][2] = f;
	m[2][0] = g;
	m[2][1] = h;
	m[2][2] = i;
}

void Matrix::Transpose() { // 주대각성분의 오른쪽 항 swap
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			swap(m[i][j], m[j][i]);
		}
	}
}

Matrix Matrix::operator+(const Matrix& a) {// 각 원소 더한 값 리턴.
	Matrix c;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			c.m[i][j] = m[i][j] + a.m[i][j];
		}
	}
	return c;
}

Matrix Matrix::operator-(const Matrix& a) {
	Matrix c;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			c.m[i][j] = m[i][j] - a.m[i][j];
		}
	}
	return c;
}

Matrix Matrix::operator*(const Matrix& a) {
	Matrix c;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			c.m[i][j] = m[i][0] * a.m[0][j] + m[i][1] * a.m[1][j] + m[i][2] * a.m[2][j];
		}
	}
	return c;
}

void Matrix::operator=(const Matrix& a) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] = a.m[i][j];
		}
	}
}

void Matrix::ShowMatrix() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
}

int Matrix::GetDet() { // aei +bfg + cdh - ceg - afg - bdi 리턴
	return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1]
		- m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0];
}
