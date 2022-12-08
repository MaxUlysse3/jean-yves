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

// Getters / Setters

int Layer::getSize() const {
	return this->size;
}

double Layer::getActivation(int index) const {
	return this->activations->get(index);
}

const MatrixVector<double>& Layer::getActivations() const {
	return *(this->activations);
}

// Iterator

Layer::Iterator::Iterator(double* ptr) : ptr(ptr) {}

double Layer::Iterator::operator * () {
	return *ptr;
}

double* Layer::Iterator::operator -> () {
	return ptr;
}

Layer::Iterator& Layer::Iterator::operator ++ () {
	ptr++;
	return *this;
}

Layer::Iterator Layer::Iterator::operator ++ (int) {
	Layer::Iterator copy(ptr);
	ptr++;
	return copy;
}

bool operator == (Layer::Iterator const& a, Layer::Iterator const& b) {
	return a.ptr == b.ptr;
}

bool operator != (Layer::Iterator const& a, Layer::Iterator const& b) {
	return a.ptr != b.ptr;
}
