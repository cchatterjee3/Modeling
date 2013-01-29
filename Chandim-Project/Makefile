#makefile for unix plateform

# Project: ModelingPeachtree


CXX  = g++
CC   = gcc


OBJ  = main.o IntersectionwithSignal.o IntersectionwoSignal.o Simulator.o Calender_queue.o
LINKOBJ  = main.o IntersectionwithSignal.o IntersectionwoSignal.o Simulator.o Calender_queue.o
LIBS = 

BIN  = ModelingPeachtree.exe
CXXFLAGS = $(CXXINCS)   -fmessage-length=0
CFLAGS = $(INCS)   -fmessage-length=0
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before ModelingPeachtree.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "ModelingPeachtree.exe" $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

IntersectionwithSignal.o: IntersectionwithSignal.cpp
	$(CPP) -c IntersectionwithSignal.cpp -o IntersectionwithSignal.o $(CXXFLAGS)

IntersectionwoSignal.o: IntersectionwoSignal.cpp
	$(CPP) -c IntersectionwoSignal.cpp -o IntersectionwoSignal.o $(CXXFLAGS)

Simulator.o: Simulator.cpp
	$(CPP) -c Simulator.cpp -o Simulator.o $(CXXFLAGS)

Calender_queue.o: Calender_queue.cc Calender_queue.h Events.h
	$(CPP) -c Calender_queue.cc -o Calender_queue.o $(CXXFLAGS)
