#include "layer.h"

Layer::Layer(Layer* previous, int size) {
	this->size = size;
	this->previous = previous;

	this->activations = new MatrixVector<double>(this->size);
	this->weights = new Matrix<double>(this->previous->size, this->size);
	this->biases = new MatrixVector<double>(this->size);
}

Layer::~Layer() {
	delete this->activations;
	delete this->weights;
	delete this->biases;
}
