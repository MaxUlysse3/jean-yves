#include "matrixOperationException.h"

#include <string>

using namespace std;

char* MatrixOperationException::what() const throw() {
	return "You cannot do this operation";
}
