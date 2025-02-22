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

Requirements:
(Note, these requirements do not cover the Elevator Controller)

For the Elevator simulator.

| REQ ID | Text                                                     |Implemented           | Tested |
|:-------| :---                                                     |:---                  |:---    |
| 001    | The elevator door shall open when a DOOR_OPEN command is |  elevator.c          |        |
|        | received.                                                |  elevator.c          |        |
| 003    | The elevator door shall close when a DOOR_CLOSE command  |                      |        |
|        | is received.                                             |                      |        |
| 002    | The elevator door will open or close in 5 seconds        |                      |        |
|        | close in 5 seconds.                                      |                      |        |
| 004    | The elevator shall STOP when an elevator command of stop |
|        | is recieved. |
| 005    | The elevator shall descend when an elevator command of |
         | GO_DOWN is recieved.                                   |
| 006    |
| 007    |
| 008    |
| 009    |
| 010    |
| 011    |
| 012    |