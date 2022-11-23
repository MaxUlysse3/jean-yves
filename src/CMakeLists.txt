cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Jean-Yves)
add_executable(a.out main.cpp)

target_include_directories(a.out PUBLIC
	"TARGET_BINARY_DIR}"
	"TARGET_SOURCE_DIR}"
	)


