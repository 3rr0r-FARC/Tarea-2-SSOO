CXX = g++
CXXFLAGS = -std=c++11 -Wall -std=c++17 -pthread  # Opción -pthread para compatibilidad con hilos
OPENCV_FLAGS = $(shell pkg-config --cflags --libs opencv4)

all: programa

programa: programa.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(OPENCV_FLAGS)

clean:
	rm -f programa
