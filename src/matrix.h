#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <concepts>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <ostream>

#include "matrixOperationException.h"

template<typename Type>
concept canBeInMatrix = requires(Type obj1, Type obj2, std::ostream stream) {
	{obj1 * obj2} -> std::same_as<Type>;
	obj1 += obj2;
	stream << obj1;
	obj1 = 0;
};

template<typename Type> requires canBeInMatrix<Type>
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
			if(this->sizeI != other.sizeI || this->sizeJ != other.sizeJ) {
				MatrixOperationException e;
				throw(e);
			}

			for(auto idx(0) ; idx<this->size ; idx++) {
				this->value[idx] = other.value[idx];
			}

			return *this;
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
			return (this->value + (idx * this->sizeJ));
		}

	protected:
		const int sizeI;
		const int sizeJ;
		const int size;
		Type* value;

};

template<typename Type> requires canBeInMatrix<Type>
std::ostream& operator << (std::ostream& stream, Matrix<Type> const& a) {
	stream << a.toString();
	return stream;
}

template<typename Type> requires canBeInMatrix<Type>
Matrix<Type> operator + (Matrix<Type> const& a, Matrix<Type> const& b) {
	Matrix<Type> toReturn(a);
	toReturn += b;
	return toReturn;
}

template<typename Type> requires canBeInMatrix<Type>
Matrix<Type> operator * (Matrix<Type> const& a, Matrix<Type> const& b) {
	if(a.getSizeI() != b.getSizeJ()) {
		MatrixOperationException e;
		throw(e);
	}

	Matrix<Type> toReturn(b.getSizeJ(), a.getSizeI());

	for(auto ARow(0) ; ARow<a.getSizeI() ; ARow++) {
		for(auto BColumn(0) ; BColumn<b.getSizeJ() ; BColumn++) {
			Type val(0);
			for(auto i(0) ; i<a.getSizeJ() ; i++) {
				val += a[ARow][i] * b[BColumn][i];
			}
			toReturn[ARow][BColumn] = val;
		}
	}

	return toReturn;
}


#endif
