# this makefile is ran from the root of the project

all: eSim

src/elevatorGUI.cxx: src/elevatorGUI.fl
	fluid -o src/elevatorGUI.cxx -h src/elevatorGUI.h -c src/elevatorGUI.fl

elevatorController/elevatorController.o:elevatorController/elevatorController.c
	${CC} -I./ -I/usr/include -I./include \
		-o elevatorController/elevatorController.o \
		-c elevatorController/elevatorController.c \
		-Wall -O0 -g -std=c11

eSim: src/elevatorGUI.cxx src/main.cxx elevatorController/elevatorController.o
	${CXX} -I./ -I/usr/include -I./include \
		src/elevatorGUI.cxx  src/main.cxx \
		elevatorController/elevatorController.o \
		-o eSim -Wall -O0 -g -lfltk

clean:
	-rm -f src/elevatorGUI.cxx src/elevatorGUI.h eSim \
		elevatorController/elevatorController.o
