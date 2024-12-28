#include <string>

#include <FL/Fl_Timer.H>

#include "elevatorGUI.h"
#include "elevator.h"

extern "C" void callback(void*) {
    tick();
    Fl::repeat_timeout(1.0, callback);
}
 
int main(int argc, char *argv[]) 
{
	UserInterfaceElevator window = UserInterfaceElevator();
	Fl_Window *w = window.make_window();
	w->show(argc, argv);

    Fl::add_timeout(1.0, callback);
	return Fl::run();
}
