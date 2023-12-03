CXX = g++
CXXFLAGS = -std=c++11 -Wall -fopenmp -std=c++17  # Añadido -fopenmp para habilitar OpenMP
OPENCV_FLAGS = $(shell pkg-config --cflags --libs opencv4)

all: openMP

openMP: openMP.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(OPENCV_FLAGS)

clean:
	rm -f openMP
