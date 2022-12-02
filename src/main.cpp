#include <iostream>
#include <string>

#include "matrix.h"
#include "matrixVector.h"
#include "layer.h"

using namespace std;

int main() {
	Matrix<int> m(2, 2);
	m[0][0] = 2;
	m[0][1] = 3;

	m[1][0] = 4;
	m[1][1] = 5;

	Matrix<int> e(2, 2);
	e[0][0] = 1;
	e[1][1] = 1;

	Matrix<int> f(m);

	cout << m << endl << e << endl;

	MatrixVector<int> v(2);
	
	v[0] = 2;
	v[1] = 5;

	cout << v << endl << m * v << endl;
}
