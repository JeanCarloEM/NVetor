cmake_minimum_required (VERSION 3.9)

SET(CMAKE_BUILD_TYPE distribution)
SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (NVetor)

file(GLOB SOURCES
	./src/RNG/*.h
	./src/RNG/*.cpp		
	./src/*.h
	./src/*.cpp
	./tests/*.h	
)

add_executable(
	runtest
	${SOURCES}
	tests.cpp
)