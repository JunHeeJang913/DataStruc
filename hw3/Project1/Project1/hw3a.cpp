#include "matrixa.h"
#include <iostream>
using namespace std;
int main() {
	Matrix matrix1(1, 2, 3, 4);
	Matrix matrix2(1, 1, 1, 1);
	Matrix matrix3;
	cout << "Matrix1 Determinant : " << matrix1.GetDet() << endl;
	cout << "Matrix2 Determinant : " << matrix2.GetDet() << endl;
	cout << "==========" << endl;
	cout << "Matrix Traspose" << endl;
	cout << "==========" << endl;
	matrix1.Transpose();
	matrix1.ShowMatrix();
	matrix1.Transpose();
	cout << "Matrix Add" << endl;
	cout << "==========" << endl;
	matrix3 = matrix1 + matrix2;
	matrix3.ShowMatrix();
	cout << "==========" << endl;
	cout << "Matrix Sub" << endl;
	cout << "==========" << endl;
	matrix3 = matrix1 - matrix2;
	matrix3.ShowMatrix();
	cout << "==========" << endl;
	cout << "Matrix Multi" << endl;
	cout << "==========" << endl;
	matrix3 = matrix1 * matrix2;
	matrix3.ShowMatrix();
	return 0;
}