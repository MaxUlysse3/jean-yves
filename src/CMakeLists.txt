cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Jean-Yves)
add_executable(a.out main.cpp)

target_link_libraries(a.out PUBLIC
	MatrixOperationException
	Layer
	)

target_include_directories(a.out PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}"
	)

add_library(MatrixOperationException matrixOperationException.cpp)

add_library(Layer layer.cpp)
