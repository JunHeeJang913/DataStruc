#include "matrixa.h"
Matrix::Matrix(int a, int b, int c, int d) {
	m[0][0] = a;	m[0][1] = b;
	m[1][0] = c;	m[1][1] = d;
}
void Matrix::Transpose(){
	Matrix temp;
	//temp�� ����-->=������ �����ε����� ��ü
	temp = *this;
	//���� Ÿ���� void �̹Ƿ� m�� �����ؾ���
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			m[i][j] = temp.m[j][i];
		}
	}
}
Matrix Matrix::operator+(const Matrix &a) {
	Matrix temp;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			temp.m[i][j] = m[i][j] + a.m[i][j];
		}
	}
	return temp;
}
Matrix Matrix::operator-(const Matrix &a){
	//������ ����
	Matrix temp;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			temp.m[i][j] = m[i][j] - a.m[i][j];
		}
	}
	return temp;
}
Matrix Matrix::operator*(const Matrix &a){
	Matrix temp;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int h = 0; h < 2; ++h) {
				temp.m[i][j] += m[i][h] * a.m[h][i];
			}
		}
	}
	return temp;
}
void Matrix::operator=(const Matrix &a){
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			m[i][j] = a.m[i][j];
		}
	}
}
void Matrix::ShowMatrix() {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}
int Matrix::GetDet(){
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}