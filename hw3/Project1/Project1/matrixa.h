#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
class Matrix {
public:
	Matrix(int a = 0, int b = 0, int c = 0, int d = 0);
	void ShowMatrix();
	void Transpose();
	int GetDet();
	Matrix operator+(const Matrix& a);
	Matrix operator-(const Matrix& a);
	Matrix operator*(const Matrix& a);
	void operator=(const Matrix& a);

private:
	int m[2][2];
	
};
#endif