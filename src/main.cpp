#include <iostream>
#include <string>

#include "matrix.h"
#include "matrixVector.h"
#include "layer.h"
#include "inputLayer.h"

using namespace std;

int main() {
	MatrixVector<int> a(5);
	a[3] = 5;

	for(auto i : a) {
		cout << i << endl;
	}

	MatrixVector<int>::Iterator z(a.begin());

	cout << *z << endl;
}
