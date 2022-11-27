#include "matrixOperationException.h"

char* MatrixOperationException::what() const throw() {
	return "You cannot do this operation";
}
