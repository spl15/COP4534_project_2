# Makefile for project 1. will make use of make all to create executable named hash,
# Make run to fully run the program, make test to incrementaly test the program, and Make clean
# to clean all .o and executables.

CXX=g++
OBJECTS= p_queue.o customer.o simulation.o
CXXFLAGS = -std=c++11 -c -g -Wall -s

# all compiles all files and then links the object files to build the sim exe
all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o sim
	
# 
p_queue.o: p_queue.cpp
	$(CXX) $(CXXFLAGS) p_queue.cpp
# 
customer.o: customer.cpp 
	$(CXX) $(CXXFLAGS) customer.cpp
#
simulation.o: simulation.cpp
	$(CXX) $(CXXFLAGS) simulation.cpp

clean:
	$(RM) *o *gch sim
