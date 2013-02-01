#makefile for unix plateform

# Project: ModelingPeachtree


CXX  = g++ -g 
CC   = g++ -g 


OBJ  = main.o Simulator.o  IntersectionwithSignal.o IntersectionwoSignal.o Intersection.o VehicleClass.o  \
		TrafficLight.o calender_queue.o
BIN = ModelingPeachtree.exe

%.cpp:
	$(CXX) -c -g -o $*.o $*.cpp

%.cc:
	$(CXX) -c -g -o $*.o $*.cc

.PHONY: all all-before all-after clean clean-custom

all: all-before ModelingPeachtree.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CXX) -g -o  $(BIN) $(OBJ) $(LIBS)

