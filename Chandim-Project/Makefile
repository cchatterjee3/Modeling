#makefile for unix plateform

# Project: ModelingPeachtree


CXX  = g++
CC   = g++


OBJ  = main.o IntersectionwithSignal.o IntersectionwoSignal.o Simulator.o calender_queue.o \
		TrafficLight.o VehicleClass.o
BIN = ModelingPeachtree.exe

.PHONY: all all-before all-after clean clean-custom

all: all-before ModelingPeachtree.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LIBS)

VehicleClass.o : VehicleClass.h
	$(CXX) -o VehicleClass.o VehicleClass.h
