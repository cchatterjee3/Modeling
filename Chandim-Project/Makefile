#makefile for unix plateform

# Project: ModelingPeachtree


CXX  = g++ -g 
CC   = g++ -g 


OBJ  = main.o calender_queue.o Intersection.o IntersectionwithSignal.o IntersectionwoSignal.o Simulator.o TrafficLight.o VehicleClass.o VehicleQueue.o RandomNum.o testing/test_aux.o testing/test1.o PostProcessing.o
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

