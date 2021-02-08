#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include "processor.h"
#include "process.h"
#include <iostream>

int main() {
 System system;
 NCursesDisplay::Display(system);
 //system.Processes(); //I used this for testing each function, using cout. I leave this and those here in comments for future development and testing 
}