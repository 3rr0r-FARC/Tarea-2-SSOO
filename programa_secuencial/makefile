CXX = g++
CXXFLAGS = -std=c++11 -Wall -std=c++17
OPENCV_FLAGS = $(shell pkg-config --cflags --libs opencv4)

all: secuencial

secuencial: secuencial.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(OPENCV_FLAGS)

clean:
	rm -f secuencial
