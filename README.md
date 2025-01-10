# elevatorSimulator

This program provides an example of an elevator simulator.  It was created
for educational purposes (specifically CSE3310).

Think of this system as 3 parts:

a.  The elevator GUI, which provides a way to provide stimulus (events) to the system. It is coded in the C++ language.  A majority was created using the fltk gui layout program known as 'fluid'.
b.  The elevator, which simulates the physical elevator. This is coded in the C programming language.
c.  The elevator controller, which controls the physical elevator based upon the inputs recieved.  It is coded in the C language.

to change the UI:

```
cd ./src
fluid elevatorGUI.fl
```

to compile the source code

```
make clean
make
```

to execute the program

```
./eSim
```


