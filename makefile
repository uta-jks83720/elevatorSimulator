# this makefile is ran from the root of the project
CC=gcc
CXX=g++
CXXOPTS=-Wall -O0 -g
COPTS=-Wall -O0 -g -std=c11
CPPFLAGS=-I./ -I/usr/include -I./include
CFLAGS=-Wall -O0 -g -std=c11

#all: eSim basicTest controllerTest1 libevsim.a
all: basicTest

# create the GUI
src/elevatorGUI.cxx: src/elevatorGUI.fl
	fluid -o src/elevatorGUI.cxx -h src/elevatorGUI.h -c src/elevatorGUI.fl

# build the library of C files
CFILES= \
./elevatorController/controllerTest1.c \
./elevatorController/basicTest.c \
./elevatorController/elevatorController.c \
./src/elevator.c \
./src/events.c 

OBJFILES=${CFILES:.c=.o}

libevsim.a: ${OBJFILES}
	ar rcs libevsim.a ${OBJFILES}
  

#eSim: src/elevatorGUI.cxx src/main.cxx elevatorController/elevatorController.o src/elevator.o
#	${CXX} -I./ -I/usr/include -I./include \
#		src/elevatorGUI.cxx  src/main.cxx   \
#	 	-o eSim ${CXXOPTS} -levsim -lfltk

basicTest: elevatorController/basicTest.c elevatorController/elevatorController.c ./src/elevator.o
	${CC} -I./ -I/usr/include -I./include \
		elevatorController/basicTest.c \
		elevatorController/elevatorController.c \
		src/elevator.o \
		-o basicTest ${COPTS}

#controllerTest1: elevatorController/controllerTest1.c elevatorController/elevatorController.c ./src/elevator.o
#	${CC} -I./ -I/usr/include -I./include \
#		elevatorController/controllerTest1.c \
#		elevatorController/elevatorController.c \
#		src/elevator.o \
#		-o controllerTest1 ${COPTS}

#test: controllerTest1 basicTest
#	./basicTest
#	./controllerTest1

clean:
	-rm -f src/elevatorGUI.cxx src/elevatorGUI.h eSim \
		elevatorController/elevatorController.o \
		${OBJFILES} libevsim.a \
		basicTest controllerTest1
