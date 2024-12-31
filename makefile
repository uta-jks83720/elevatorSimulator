# this makefile is ran from the root of the project
CC=gcc
CXX=g++
CXXOPTS=-Wall -O0 -g
COPTS=-Wall -O0 -g -std=c11
CPPFLAGS=-I./ -I/usr/include -I./include
CFLAGS=-Wall -O0 -g -std=c11

#all: eSim basicTest controllerTest1 libevsim.a
all: basicTest controllerTest1

# create the GUI
src/elevatorGUI.cxx: src/elevatorGUI.fl
	fluid -o src/elevatorGUI.cxx -h src/elevatorGUI.h -c src/elevatorGUI.fl

# build the library of C files
CFILES= \
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

basicTest: elevatorController/basicTest.c libevsim.a
	${CC} ${CPPFLAGS} \
		elevatorController/basicTest.c \
		-o basicTest ${COPTS} -L./ -levsim

controllerTest1: elevatorController/controllerTest1.c libevsim.a
	${CC} ${CPPFLAGS} \
		elevatorController/controllerTest1.c \
		-o controllerTest1 ${COPTS} -L./ -levsim

test: controllerTest1 basicTest
	./basicTest
	./controllerTest1

clean:
	-rm -f src/elevatorGUI.cxx src/elevatorGUI.h eSim \
		elevatorController/elevatorController.o \
		${OBJFILES} libevsim.a \
		basicTest controllerTest1
