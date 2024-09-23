CXX=g++
CXXFLAGS=-std=c++11 -pthread -Wall -Wextra

all: main

main: main.o DiningPhilosophers.o
	$(CXX) $(CXXFLAGS) -o main main.o DiningPhilosophers.o

main.o: main.cpp DiningPhilosophers.h
	$(CXX) $(CXXFLAGS) -c main.cpp

DiningPhilosophers.o: DiningPhilosophers.cpp DiningPhilosophers.h
	$(CXX) $(CXXFLAGS) -c DiningPhilosophers.cpp

clean:
	rm -f *.o main