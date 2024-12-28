# this makefile is ran from the root of the project

CXXOPTS=-Wall -O0 -g
COPTS=-Wall -O0 -g -std=c11
CPPFLAGS=-I./ -I/usr/include -I./include
CFLAGSS=-Wall -O0 -g -std=c11

all: eSim

src/elevatorGUI.cxx: src/elevatorGUI.fl
	fluid -o src/elevatorGUI.cxx -h src/elevatorGUI.h -c src/elevatorGUI.fl

elevatorController/elevatorController.o:elevatorController/elevatorController.c
	${CC} -I./ -I/usr/include -I./include \
		-o elevatorController/elevatorController.o \
		-c elevatorController/elevatorController.c \
		${COPTS}

eSim: src/elevatorGUI.cxx src/main.cxx elevatorController/elevatorController.o src/elevator.o
	${CXX} -I./ -I/usr/include -I./include \
		src/elevatorGUI.cxx  src/main.cxx src/elevator.o \
		elevatorController/elevatorController.o \
		-o eSim ${CXXOPTS} -lfltk

clean:
	-rm -f src/elevatorGUI.cxx src/elevatorGUI.h eSim \
		elevatorController/elevatorController.o
