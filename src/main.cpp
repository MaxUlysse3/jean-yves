#include <iostream>
#include <string>

#include "matrix.h"
#include "matrixVector.h"
#include "layer.h"
#include "inputLayer.h"

using namespace std;

int main() {
	Matrix<int> a(5, 4);
	a[3][2] = 5;

	for(auto i : a) {
		cout << i << endl;
	}

	Matrix<int>::Iterator z(a.begin());

	cout << *z << endl << a << endl;
}
