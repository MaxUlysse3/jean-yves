#ifndef MATRIXVECTOR_H_INCLUDED
#define MATRIXVECTOR_H_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include <iterator>

#include "matrix.h"

template<typename Type> requires canBeInMatrix<Type>
class MatrixVector {
	public:
		MatrixVector(int size) : size(size) {
			this->value = new Type[this->size];
			for(auto i(0) ; i<this->size ; i++) {
				this->value[i] = 0;
			}
		}

		MatrixVector(MatrixVector<Type> const& other) : size(other.size) {
			this->value = new Type[this->size];
			for(auto i(0) ; i<this->size ; i++) {
				this->value[i] = other.value[i];
			}
		}

		~MatrixVector() {
			delete[] this->value;
		}

		void set(int index, Type val) {
			this->value[index] = val;
		}

		Type get(int index) const {
			return this->value[index];
		}

		int getSize() const {
			return this->size;
		}

		std::string toString() const {
			std::stringstream toReturn;
			for(auto i(0) ; i<this->size ; i++) {
				toReturn << this->value[i] << " ";
			}
			toReturn << std::endl;

			return toReturn.str();
		}

		MatrixVector<Type>& operator = (MatrixVector<Type> const& other) {
			if(this->size != other.size) {
				MatrixOperationException e;
				throw(e);
			}

			for(auto i(0) ; i<this->size ; i++) {
				this->value[i] = other.value[i];
			}

			return *this;
		}

		MatrixVector<Type>& operator += (MatrixVector<Type> const& other) {
			if(this->size != other.size) {
				MatrixOperationException e;
				throw(e);
			}

			for(auto i(0) ; i<this->size ; i++) {
				this->value[i] += other.value[i];
			}
		}

		Type& operator [] (int index) const {
			return this->value[index];
		}

		MatrixVector<Type>& operator *= (Matrix<Type> const& matrix) {
			if(this->size != matrix.getSizeJ()) {
				MatrixOperationException e;
				throw(e);
			}

			Type tempValues[this->size];

			for(auto matrixLine(0) ; matrixLine<matrix.getSizeI() ; matrixLine++) {
				Type val(0);
				for(auto i(0) ; i<this->size ; i++) {
					val += (this->value[i] * matrix.get(matrixLine, i));
				}
				tempValues[matrixLine] = val;
			}


			for(auto i(0) ; i<this->size ; i++) {
				this->value[i] = tempValues[i];
			}

			return *this;
		}

		struct Iterator {
			public:
				Iterator(Type* ptr) : ptr(ptr) {}

				Type& operator * () {
					return *ptr;
				}

				Type* operator -> () {
					return ptr;
				}

				Iterator& operator ++ () {
					ptr++;
					return *this;
				}

				Iterator operator ++ (int) {
					Iterator copy(*this);
					++(*this);
					return copy;
				}

				friend bool operator == (Iterator const& a, Iterator const& b) {
					return a.ptr == b.ptr;
				}

				friend bool operator != (Iterator const& a, Iterator const& b) {
					return a.ptr != b.ptr;
				}

			private:
				Type* ptr;
		};

		Iterator begin() const {
			return Iterator(this->value);
		}

		Iterator end() const {
			return Iterator(this->value + this->size);
		}
	
	protected:
		const int size;
		Type* value;

};

template<typename Type> requires canBeInMatrix<Type>
std::ostream& operator << (std::ostream& stream, MatrixVector<Type> const& vector) {
	stream << vector.toString();
	return stream;
}

template<typename Type> requires canBeInMatrix<Type>
MatrixVector<Type> operator + (MatrixVector<Type> const& a, MatrixVector<Type> const& b) {
	MatrixVector<Type> toReturn(a);
	toReturn += b;

	return toReturn;
}

template<typename Type> requires canBeInMatrix<Type>
MatrixVector<Type> operator * (Matrix<Type> const& matrix, MatrixVector<Type> const& vector) {
	if(matrix.getSizeJ() != vector.getSize()) {
		MatrixOperationException e;
		throw(e);
	}

	MatrixVector<Type> toReturn(vector);
	toReturn *= matrix;

	return toReturn;
}

#endif
