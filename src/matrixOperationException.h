#ifndef MATRIXOPERATIONEXCEPTION_H_INCLUDED
#define MATRIXOPERATIONEXCEPTION_H_INCLUDED

#include <exception>

class MatrixOperationException : public std::exception {
	public :
		char* what() const throw();
};

#endif
