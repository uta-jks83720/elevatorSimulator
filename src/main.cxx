#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include "elevatorGUI.h"


int main(int argc, char *argv[]) 
{
	UserInterfaceElevator window = UserInterfaceElevator();
	Fl_Window *w = window.make_window();
	w->show(argc, argv);
	return Fl::run();
}
