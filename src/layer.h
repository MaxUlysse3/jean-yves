#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include "matrix.h"
#include "matrixVector.h"

class Layer {
	public:
		Layer(Layer* previous, int size);
		~Layer();

		// Getters / Setters

		int getSize() const;
		double getActivation(int index) const;
		const MatrixVector<double>& getActivations() const;

		// Iterator
		
		struct Iterator {
			public:
				Iterator(double* ptr);

				double operator * ();
				double* operator -> ();

				Iterator& operator ++ ();
				Iterator operator ++ (int);

				friend bool operator == (Iterator const& a, Iterator const& b);
				friend bool operator != (Iterator const& a, Iterator const& b);

			private:
				double* ptr;
		};

		Iterator begin();
		Iterator end();
	
	protected:
		MatrixVector<double>* activations;
		Matrix<double>* weights;
		MatrixVector<double>* biases;

		Layer* previous;

		int size;

};

#endif
