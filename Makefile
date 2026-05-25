CXX = g++
CXXFLAGS = -std=c++23 -Wall
LIBS = -lraylib

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main $(LIBS)

clean:
	rm -f main *.o