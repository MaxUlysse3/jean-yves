#ifndef MATRIXVECTOR_H_INCLUDED
#define MATRIXVECTOR_H_INCLUDED

#include "matrix.h"

template<typename Type> requires canBeInMatrix<Type>
class MatrixVector : public Matrix {
	MatrixVector(int size) : sizeJ(size), sizeI(1), size(size) {
		this->value = new Type[this->size];
		for(auto i(0) ; i<this->size ; i++) {
			this->value[i] = 0;
		}
	}
}

#endif
