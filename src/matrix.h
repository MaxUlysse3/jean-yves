#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <concepts>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <ostream>

#include "matrixOperationException.h"

template<typename Type> requires std::convertible_to<Type, double>
class Matrix {
	public:
		Matrix(int sizeI, int sizeJ) : sizeI(sizeI), sizeJ(sizeJ), size(sizeI * sizeJ) {

			this->value = new Type[this->size];
			for(auto idx(0);idx<this->size;idx++) {
				this->value[idx] = 0;
			}
		}

		Matrix(Matrix<Type> const& other) : sizeI(other.sizeI), sizeJ(other.sizeJ), size(other.size) {
			this->value = new Type[this->size];
			for(auto idx(0);idx<this->size;idx++) {
				this->value[idx] = other.value[idx];
			}
		}

		~Matrix() {
			delete[] this->value;
		}

		void set(int i, int j, Type val) {
			this->value[(i * this->sizeJ) + j] =  val;
		}

		Type get(int i, int j) const {
			return this->value[(i * this->sizeJ) + j];
		}

		int getSizeI() const {
			return this->sizeI;
		}
		int getSizeJ() const {
			return this->sizeJ;
		}
		int getSize() const {
			return this->size;
		}

		std::string toString() const {
			std::stringstream toReturn;

			for(auto idx(0) ; idx<this->size ; idx++) {
				toReturn << this->value[idx];
				if((idx + 1) % this->sizeJ == 0) {
					toReturn << std::endl;
				} else {
					toReturn << " ";
				}
			}
			return toReturn.str();
		}

		Matrix<Type>& operator = (Matrix<Type> const& other) {
			this->sizeI = other.sizeI;
			this->sizeJ = other.sizeJ;
			this->size = other.size;

			for(auto idx(0) ; idx<this->size ; idx++) {
				this->value[idx] = other.value[idx];
			}
		}

		Matrix<Type>& operator += (Matrix<Type> const& other) {
			if(other.sizeI != this->sizeI || other.sizeJ != this->sizeJ) {
				MatrixOperationException e;
				throw(e);
			}

			for(auto idx(0) ; idx<this->size ; idx++) {
				this->value[idx] += other.value[idx];
			}
			return *this;
		}

		Type* operator [] (int idx) const {
			return (this->value + idx);
		}



	protected:
		const int sizeI;
		const int sizeJ;
		const int size;
		Type* value;

};

template<typename Type>
std::ostream& operator << (std::ostream& stream, Matrix<Type> const& a) {
	stream << a.toString();
	return stream;
}

template<typename Type>
Matrix<Type> operator + (Matrix<Type> const& a, Matrix<Type> const& b) {
	Matrix<Type> toReturn(a);
	toReturn += b;
	return toReturn;
}

template<typename Type>
Matrix<Type> operator * (Matrix<Type> const& a, Matrix<Type> const& b) {
	if(b.getSizeI() != a.getSizeJ()) {
		MatrixOperationException e;
		throw(e);
	}

	Matrix<Type> toReturn(a.getSizeJ(), b.getSizeI());

	for(auto idx(0) ; idx<a.getSizeI() ; idx++) {
		for(auto idx2(0) ; idx2<b.getSizeJ() ; idx2++) {
			Type val(0);
			for(auto idx3(0) ; idx3<a.getSizeJ() ; idx3++) {
				val += a[idx][idx3] * b[idx2][idx];
			}
			toReturn[idx][idx2] = val;
		}
	}

	return toReturn;
}


#endif
