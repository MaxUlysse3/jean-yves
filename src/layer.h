#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include "matrix.h"
#include "matrixVector.h"

class Layer {
	public:
		Layer(Layer* previous, int size);
		~Layer();

		int getSize() const;
		double getActivation(int index) const;
	
	private:
		MatrixVector<double>* activations;
		Matrix<double>* weights;
		MatrixVector<double>* biases;

		Layer* previous;

		int size;

};

#endif
