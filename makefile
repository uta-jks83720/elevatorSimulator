#this makefile is ran from the root of the project

all: eSim
src/elevatorGUI.cxx: src/elevatorGUI.fl
	fluid -o src/elevatorGUI.cxx -h src/elevatorGUI.h -c src/elevatorGUI.fl
eSim: src/elevatorGUI.cxx src/main.cxx
	${CXX} -I./ -I/usr/include -I./include \
		src/elevatorGUI.cxx  src/main.cxx \
		-o eSim -Wall -O0 -g -lfltk
clean:
	-rm -f src/elevatorGUI.cxx src/elevatorGUI.h eSim
