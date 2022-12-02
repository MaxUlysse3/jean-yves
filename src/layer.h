#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include "matrix.h"
#include "matrixVector.h"

class Layer {
	public:
		Layer(Layer previous);

		int getSize const;
	
	private:
		MatrixVector<double> activations;
		Matrix<double> weights;
		MatrixVector<double> biases;

		Layer& previous;

		int size;

};

#endif
