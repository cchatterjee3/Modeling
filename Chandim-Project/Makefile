#makefile for unix plateform

# Project: ModelingPeachtree


CXX  = g++
CC   = g++


OBJ  = main.o Simulator.o  IntersectionwithSignal.o IntersectionwoSignal.o Intersection.o VehicleClass.o  \
		TrafficLight.o calender_queue.o
BIN = ModelingPeachtree.exe

.PHONY: all all-before all-after clean clean-custom

all: all-before ModelingPeachtree.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LIBS)

