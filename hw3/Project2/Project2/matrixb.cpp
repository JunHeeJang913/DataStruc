#include "matrixb.h"
Matrix::Matrix(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
	m[0][0] = a;	m[0][1] = b;	m[0][2] = c;
	m[1][0] = d;	m[1][1] = e;	m[1][2] = f;
	m[2][0] = g;	m[2][1] = h;	m[2][2] = i;
}
void Matrix::Transpose() {
	Matrix temp;
	//temp에 전달-->=연산자 오버로딩으로 대체
	temp = *this;
	//리턴 타입이 void 이므로 m을 수정해야함
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m[i][j] = temp.m[j][i];
		}
	}
}
Matrix Matrix::operator+(const Matrix &a) {
	Matrix temp;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			temp.m[i][j] = m[i][j] + a.m[i][j];
		}
	}
	return temp;
}
Matrix Matrix::operator-(const Matrix &a) {
	//덧셈과 동일
	Matrix temp;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			temp.m[i][j] = m[i][j] - a.m[i][j];
		}
	}
	return temp;
}
Matrix Matrix::operator*(const Matrix &a) {
	Matrix temp;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int h = 0; h < 3; ++h) {
				temp.m[i][j] += m[i][h] * a.m[h][i];
			}
		}
	}
	return temp;
}
void Matrix::operator=(const Matrix &a) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m[i][j] = a.m[i][j];
		}
	}
}
void Matrix::ShowMatrix() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}
int Matrix::GetDet() {
	return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) + m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
}